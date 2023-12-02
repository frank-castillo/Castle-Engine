#pragma once

#include <CASTLE_Engine/Inc/CASTLE_Engine.h>

using namespace CASTLEEngine;
using namespace CASTLEEngine::CEMath;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::Input;

class FogEffect
{
public:
    void Initialize();
    void Terminate();

    void Begin();
    void End();

    void Render(const RenderObject& renderObject);

    void SetFogValues(float fogStart, float fogEnd);
    void SetCamera(const Camera& camera);

    void DebugUI();

private:
    struct TransformData
    {
        CEMath::Matrix4 worldMatrix;
        CEMath::Matrix4 viewMatrix;
        CEMath::Matrix4 projectionMatrix;
    };

    struct FogData
    {
        float fogStart;
        float fogEnd;
        float padding1, padding2;
    };

    using TransformBuffer = TypedConstantBuffer<TransformData>;
    using FogDataBuffer = TypedConstantBuffer<FogData>;

    TransformBuffer mTransformBuffer;
    FogDataBuffer mFogDataBuffer;

    TextureId mTextureId;
    VertexShader mVertexShader;
    PixelShader mPixelShader;
    Sampler mSampler;

    const Camera* mCamera = nullptr;

    float mFogStart;
    float mFogEnd;
};