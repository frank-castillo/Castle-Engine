#pragma once

#include <CASTLE_Engine/Inc/Component.h>
#include "TypeIds.h"

namespace CASTLEEngine
{
    class CameraComponent;
    class TransformComponent;
}

class ThirdPersonCameraComponent final : public Component
{
public:
    SET_TYPE_ID(CustomComponentId::ThirdPersonCameraComponent);

    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void DebugUI();

    void SetMoveSpeed(float speed) { mMoveSpeed = speed; }
    void SetTurnSpeed(float speed) { mTurnSpeed = speed; }

private:
    CASTLEEngine::CEMath::Vector3 mCameraOffset = {0.0f, 2.0f, 2.5f};
    CASTLEEngine::CEMath::Vector3 mCameraLookAt = { 0.0f, 1.5f, 0.0f };
    CASTLEEngine::CameraComponent* mCameraComponent;
    CASTLEEngine::TransformComponent* mParentTransform;

    float mMoveSpeed = 1.0f;
    float mTurnSpeed = 0.1f;
};
