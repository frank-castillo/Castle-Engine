#include "ThirdPersonCameraComponent.h"
#include <CASTLE_Engine/Inc/GameObject.h>
#include <CASTLE_Engine/Inc/GameWorld.h>
#include "CASTLE_Engine/Inc/CameraComponent.h"
#include "CASTLE_Engine/Inc/TransformComponent.h"

using namespace CASTLEEngine::CEMath;

void ThirdPersonCameraComponent::Initialize()
{
    mCameraComponent = GetOwner().GetComponent<CameraComponent>();
    mParentTransform = GetOwner().GetComponent<TransformComponent>();
    ASSERT(mCameraComponent != nullptr, "ThirdPersonCameraComponent: Parent object does not contain a camera component");
}

void ThirdPersonCameraComponent::Terminate()
{
    mCameraComponent = nullptr;
}

void ThirdPersonCameraComponent::Update(float deltaTime)
{
    Matrix4 worldTransform = mParentTransform->GetMatrix4();
    Vector3 worldPosition = TransformCoord(mCameraOffset, worldTransform);
    Vector3 worldLookAt = TransformCoord(mCameraLookAt, worldTransform);

    mCameraComponent->GetCamera().SetPosition(worldPosition);
    mCameraComponent->GetCamera().SetLookAt(worldLookAt);

    // Have an offset for X,Y,Z
    // Have a LookAt Location
    // Convert to LookAt matrix
    // Keep them local space
    // Get camera position and lookat, multiply by player transform, converting this to world space
}

void ThirdPersonCameraComponent::DebugUI()
{
    ImGui::LabelText("Third Person Camera Component", "");

    ImGui::DragFloat3("Camera Offset", &mCameraOffset.x, 0.5f, -100.0f, 100.0f);
    ImGui::DragFloat3("Camera Look At", &mCameraLookAt.x, 0.5f, -100.0f, 100.0f);
}
