#include "Precompiled.h"

#include "PlayerInputControllerComponent.h"
#include "PlayerControllerComponent.h"
#include "GameObject.h"
#include "Input/Inc/InputSystem.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Input;
using namespace CASTLEEngine::CEMath;

void PlayerInputControllerComponent::Initialize()
{
    mPlayerController = GetOwner().GetComponent<PlayerControllerComponent>();
    ASSERT(mPlayerController != nullptr, "PlayerInputControllerComponent: Gameobject has no PlayerControllerComponent");

    mDirection = Vector3::Zero;
}

void PlayerInputControllerComponent::Terminate()
{
    mPlayerController = nullptr;
}

void PlayerInputControllerComponent::Update(float deltaTime)
{
    auto input = InputSystem::Get();

    if (input->IsKeyPressed(KeyCode::SPACE))
    {
        mPlayerController->Jump();
    }

    if (input->IsKeyDown(KeyCode::UP))
    {
        mPlayerController->Move(Vector3::ZAxis, deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::DOWN))
    {
        mPlayerController->Move(Vector3::ZAxis * -1.0f, deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::LEFT))
    {
        mPlayerController->Move(Vector3::XAxis, deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::RIGHT))
    {
        mPlayerController->Move(Vector3::XAxis * -1.0f, deltaTime);
    }
    else
    {
        mPlayerController->Reset();
    }
}

void PlayerInputControllerComponent::DebugUI()
{

}
