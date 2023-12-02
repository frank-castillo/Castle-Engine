#pragma once

#include <CASTLE_Engine/Inc/CASTLE_Engine.h>

using namespace CASTLEEngine;
using namespace CASTLEEngine::CEMath;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::Input;

class StandardFogState : public CASTLEEngine::AppState
{
public:
    virtual ~StandardFogState() = default;

    virtual void Initialize() override;
    virtual void Terminate() override;

    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void DebugUI() override;

protected:
    Camera mCamera;
    DirectionalLight mDirectionalLight;

    Mesh mSphere;
    RenderGroup mCharacter;
    RenderObject mGround;

    StandardFogEffect mStandardFogEffect;
    ShadowEffect mShadowEffect;
    BlendState mAlphaBlendState;
};