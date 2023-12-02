#pragma once

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
    CASTLEEngine::Graphics::Camera mCamera;

    bool mIsLine = true;
    CASTLEEngine::CEMath::Vector3 mLinePos1 = CASTLEEngine::CEMath::Vector3::Zero;
    CASTLEEngine::CEMath::Vector3 mLinePos2 = CASTLEEngine::CEMath::Vector3::One;
    CASTLEEngine::Color mLineColor = CASTLEEngine::Colors::Cyan;

    int mSlices = 10;
    int mRings = 10;
    float mCircleRadius = 1.0f;
    CASTLEEngine::Color mCircleColor = CASTLEEngine::Colors::Cyan;
};