#include "Precompiled.h"
#include "AnimationUtil.h"
#include "StandardFogEffect.h"
#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;

static constexpr size_t MaxBoneCount = 256;

void StandardFogEffect::Initialize(const std::filesystem::path& filePath)
{
    mTransformBuffer.Initialize();
    mBoneTransformBuffer.Initialize(MaxBoneCount * sizeof(CEMath::Matrix4));
    mLightBuffer.Initialize();
    mMaterialBuffer.Initialize();
    mSettingsBuffer.Initialize();
    mFogDataBuffer.Initialize();

    mVertexShader.Initialize<Vertex>(filePath);
    mPixelShader.Initialize(filePath);
    mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void StandardFogEffect::Terminate()
{
    mSampler.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
    mFogDataBuffer.Terminate();
    mSettingsBuffer.Terminate();
    mMaterialBuffer.Terminate();
    mLightBuffer.Terminate();
    mBoneTransformBuffer.Terminate();
    mTransformBuffer.Terminate();
}

void StandardFogEffect::Begin()
{
    ASSERT(mCamera != nullptr, "Standard Effect - No Camera Set!");
    ASSERT(mDirectionalLight != nullptr, "Standard Effect - No Light Set!");

    mVertexShader.Bind();
    mPixelShader.Bind();

    mTransformBuffer.BindVS(0);

    mBoneTransformBuffer.BindVS(1);

    mLightBuffer.BindVS(2);
    mLightBuffer.BindPS(2);

    mMaterialBuffer.BindVS(3);
    mMaterialBuffer.BindPS(3);

    mSettingsBuffer.BindVS(4);
    mSettingsBuffer.BindPS(4);

    mFogDataBuffer.BindVS(5);
    mFogDataBuffer.BindPS(5);

    mSampler.BindVS(0);
    mSampler.BindPS(0);
}

void StandardFogEffect::End()
{
    if (mShadowMap != nullptr)
    {
        Texture::UnbindPS(4);
    }
}

void StandardFogEffect::Render(const RenderObject& renderObject)
{
    const auto& matWorld = renderObject.transform.GetMatrix4();
    const auto& matView = mCamera->GetViewMatrix();
    const auto& matProj = mCamera->GetProjectionMatrix();

    SettingsData settingsData;
    settingsData.useDiffuseMap = mSettingsData.useDiffuseMap > 0 && renderObject.diffuseMapId > 0;
    settingsData.useSpecularMap = mSettingsData.useSpecularMap > 0 && renderObject.specularMapId > 0;
    settingsData.useDisplacementMap = mSettingsData.useDisplacementMap > 0 && renderObject.displacementMapId > 0;
    settingsData.useNormalMap = mSettingsData.useNormalMap > 0 && renderObject.normalMapId > 0;
    settingsData.useShadowMap = mSettingsData.useShadowMap > 0 && mShadowMap != nullptr;
    settingsData.useSkinning = mSettingsData.useSkinning > 0 && renderObject.skeleton != nullptr;
    settingsData.depthBias = mDepthBias;
    settingsData.useFog = mSettingsData.useFog;

    TransformData transformData;
    transformData.world = Transpose(matWorld);
    transformData.wvp[0] = Transpose(matWorld * matView * matProj);
    transformData.viewPosition = mCamera->GetPosition();
    transformData.displacementWeight = mDisplacementWeight;

    if (settingsData.useShadowMap)
    {
        const auto& matLightView = mLightCamera->GetViewMatrix();
        const auto& matLightProj = mLightCamera->GetProjectionMatrix();
        transformData.wvp[1] = Transpose(matWorld * matLightView * matLightProj);

        mShadowMap->BindPS(4);
    }

    if (settingsData.useSkinning)
    {
        AnimationUtil::BoneTransforms boneTransforms;
        AnimationUtil::ComputeBoneTransform(renderObject.modelId, boneTransforms, renderObject.animator);
        AnimationUtil::ApplyBoneOffsets(renderObject.modelId, boneTransforms);

        for (auto& transform : boneTransforms)
        {
            transform = CEMath::Transpose(transform);
        }

        boneTransforms.resize(BoneTransformData::MaxBoneCount);
        mBoneTransformBuffer.Update(boneTransforms.data());
    }

    FogData fogData;

    if (settingsData.useFog)
    {
        fogData.fogColor = mFogColor;
        fogData.fogStart = mFogStart;
        fogData.fogEnd = mFogEnd;
    }

    mTransformBuffer.Update(transformData); // Data to transform the shader
    mLightBuffer.Update(*mDirectionalLight);
    mMaterialBuffer.Update(renderObject.material);
    mSettingsBuffer.Update(settingsData);
    mFogDataBuffer.Update(fogData);

    // Send data to shader and display
    auto tm = TextureManager::Get();
    tm->BindPS(renderObject.diffuseMapId, 0);
    tm->BindPS(renderObject.normalMapId, 1); // New socket for binding normal color information
    tm->BindVS(renderObject.displacementMapId, 2); // New socket for binding normal color information
    tm->BindPS(renderObject.specularMapId, 3); // New socket for binding normal color information
    renderObject.meshBuffer.Render();
}

void StandardFogEffect::SetCamera(const Camera& camera)
{
    mCamera = &camera;
}

void StandardFogEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
    mDirectionalLight = &directionalLight;
}

void StandardFogEffect::SetLightCamera(const Camera& camera)
{
    mLightCamera = &camera;
}

void StandardFogEffect::SetShadowMap(const Texture* shadowMap)
{
    mShadowMap = shadowMap;
}

void StandardFogEffect::DebugUI()
{
    ImGui::Separator();

    if (ImGui::CollapsingHeader("StandardEffect", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::DragFloat("Displacement Weight", &mDisplacementWeight, 0.01f, 0.0f, 10.0f);

        bool useDiffuseMap = mSettingsData.useDiffuseMap > 0;
        ImGui::Checkbox("Use Diffuse Map", &useDiffuseMap);
        mSettingsData.useDiffuseMap = (useDiffuseMap) ? 1 : 0;

        bool useSpecularMap = mSettingsData.useSpecularMap > 0;
        ImGui::Checkbox("Use Specular Map", &useSpecularMap);
        mSettingsData.useSpecularMap = (useSpecularMap) ? 1 : 0;

        bool useDisplacementMap = mSettingsData.useDisplacementMap > 0;
        ImGui::Checkbox("Use Displacement Map", &useDisplacementMap);
        mSettingsData.useDisplacementMap = (useDisplacementMap) ? 1 : 0;

        bool useNormalMap = mSettingsData.useNormalMap > 0;
        ImGui::Checkbox("Use Normal Map", &useNormalMap);
        mSettingsData.useNormalMap = (useNormalMap) ? 1 : 0;

        bool useShadowMap = mSettingsData.useShadowMap > 0;
        ImGui::Checkbox("Use Shadow Map", &useShadowMap);
        mSettingsData.useShadowMap = (useShadowMap) ? 1 : 0;

        bool useFogShader = mSettingsData.useFog > 0;
        ImGui::Checkbox("Use Fog Shader", &useFogShader);
        mSettingsData.useFog = (useFogShader) ? 1 : 0;

        ImGui::DragFloat("Depth Bias", &mDepthBias, 0.0000001f, 0.0f, 1.0f, "%.6f");
        
        ImGui::Text("Fog Values");
        ImGui::DragFloat("Fog Start", &mFogStart, 1.0f, 1.0f, 1000.0f);
        ImGui::DragFloat("Fog End", &mFogEnd, 1.0f, 1.0f, 1000.0f);
        ImGui::ColorEdit4("Fog##Color", &mFogColor.r);
    }
}