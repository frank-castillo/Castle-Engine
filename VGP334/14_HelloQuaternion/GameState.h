#pragma once

#include <CASTLE_Engine/Inc/CASTLE_Engine.h>

using namespace CASTLEEngine;
using namespace CASTLEEngine::CEMath;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::Input;

class GameState : public CASTLEEngine::AppState
{
public:
    virtual ~GameState() = default;

    virtual void Initialize() override;
    virtual void Terminate() override;

    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void DebugUI() override;

protected:
    Camera mCamera;
    DirectionalLight mDirectionalLight;

    RenderObject mSphere;
    RenderObject mGround;
    StandardEffect mStandardEffect;
    float mYaw = 0.0f;
    float mRoll = 0.0f;
    float mPitch = 0.0f;
};