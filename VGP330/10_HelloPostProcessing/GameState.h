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
    virtual void ShowNormals();

    Camera mCamera;
    DirectionalLight mDirectionalLight;

    Mesh mSphere;
    RenderObject mEarthObject;
    RenderObject mScreenQuad;

    RenderTarget mRenderTarget;

    StandardEffect mStandardEffect;
    PostProcessingEffect mPostProcessingEffect;

    bool mShowNormals = false;
};