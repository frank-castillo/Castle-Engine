#pragma once

#include "ConstantBuffer.h"
#include "LightType.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "Material.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::CEMath;
using namespace CASTLEEngine::Graphics;

namespace CASTLEEngine::Graphics
{
    class Camera;
    class RenderObject;
    class Texture;

    class StandardFogEffect
    {
    public:
        void Initialize(const std::filesystem::path& filePath);
        void Terminate();

        void Begin();
        void End();

        void Render(const RenderObject& renderObject);

        void SetCamera(const Camera& camera);
        void SetDirectionalLight(const DirectionalLight& directionalLight);
        void SetLightCamera(const Camera& camera);
        void SetShadowMap(const Texture* shadowMap);

        void DebugUI();

    private:
        struct TransformData
        {
            Matrix4 world;
            Matrix4 wvp[2];
            Vector3 viewPosition;
            float displacementWeight;
        };

        struct BoneTransformData
        {
            static constexpr size_t MaxBoneCount = 256;
            CEMath::Matrix4 boneTransforms[MaxBoneCount];
        };

        struct SettingsData
        {
            int useDiffuseMap = 1;
            int useSpecularMap = 1;
            int useDisplacementMap = 1;
            int useNormalMap = 1;
            int useShadowMap = 1;
            int useFog = 1;
            int useSkinning = 1;
            float depthBias = 0.0f;
        };

        struct FogData
        {
            Color fogColor;
            float fogStart;
            float fogEnd;
            float padding[2] = { 0.0f };
        };

        using TransformBuffer = TypedConstantBuffer<TransformData>;
        using BoneTransformBuffer = ConstantBuffer;
        using LightBuffer = TypedConstantBuffer<DirectionalLight>;
        using MaterialBuffer = TypedConstantBuffer<Material>;
        using SettingsBuffer = TypedConstantBuffer<SettingsData>;
        using FogDataBuffer = TypedConstantBuffer<FogData>;

        TransformBuffer mTransformBuffer;
        BoneTransformBuffer mBoneTransformBuffer;
        LightBuffer mLightBuffer;
        MaterialBuffer mMaterialBuffer;
        SettingsBuffer mSettingsBuffer;
        FogDataBuffer mFogDataBuffer;
        Sampler mSampler;

        VertexShader mVertexShader;
        PixelShader mPixelShader;

        SettingsData mSettingsData;
        FogData mFogData;

        Color mFogColor = Colors::White;
        float mDisplacementWeight = 0.0f;
        float mDepthBias = 0.0f;
        float mFogStart = 1.0f;
        float mFogEnd = 6.0f;
        bool mUseFog = true;

        const Camera* mCamera = nullptr;
        const Camera* mLightCamera = nullptr;
        const DirectionalLight* mDirectionalLight = nullptr;
        const Texture* mShadowMap = nullptr;
    };
}