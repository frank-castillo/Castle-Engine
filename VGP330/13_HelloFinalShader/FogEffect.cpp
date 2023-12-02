#include "FogEffect.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;

void FogEffect::Initialize()
{
    std::filesystem::path shaderFile = L"../../Assets/Shaders/DoFog.fx";
    mTextureId = TextureManager::Get()->LoadTexture(L"Textures/noise.png");

    mTransformBuffer.Initialize();
    mFogDataBuffer.Initialize();

    mVertexShader.Initialize<Vertex>(shaderFile);
    mPixelShader.Initialize(shaderFile);
    mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void FogEffect::Terminate()
{
    mSampler.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
    mFogDataBuffer.Terminate();
    mTransformBuffer.Terminate();
}

void FogEffect::Begin()
{
    mVertexShader.Bind();
    mPixelShader.Bind();

    mTransformBuffer.BindVS(0);
    //mTransformBuffer.BindPS(0);
    TextureManager::Get()->BindPS(mTextureId, 0);

    //mFogDataBuffer.BindPS(1);
    mFogDataBuffer.BindVS(1);

    mSampler.BindVS(0);
    mSampler.BindPS(0);
}

void FogEffect::End()
{
    Texture::UnbindPS(0);
}

void FogEffect::Render(const RenderObject& renderObject)
{
    const auto& matWorld = renderObject.transform.GetMatrix4();
    const auto& matView = mCamera->GetViewMatrix();
    const auto& matProj = mCamera->GetProjectionMatrix();

    TransformData transformData;
    transformData.worldMatrix = CEMath::Transpose(matWorld);
    transformData.viewMatrix = CEMath::Transpose(matView);
    transformData.projectionMatrix = CEMath::Transpose(matProj);

    FogData fogData;
    fogData.fogStart = mFogStart;
    fogData.fogEnd = mFogEnd;

    mTransformBuffer.Update(transformData);
    mFogDataBuffer.Update(fogData);

    renderObject.meshBuffer.Render();
}

void FogEffect::SetFogValues(float fogStart, float fogEnd)
{
    mFogStart = fogStart;
    mFogEnd = fogEnd;
}

void FogEffect::SetCamera(const Camera& camera)
{
    mCamera = &camera;
}

void FogEffect::DebugUI()
{
    if (ImGui::CollapsingHeader("FogEffect", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Fog Values");
        ImGui::DragFloat("Fog Start", &mFogStart, 1.0f, 1.0f, 1000.0f);
        ImGui::DragFloat("Fog End", &mFogEnd, 1.0f, 1.0f, 1000.0f);
    }
}