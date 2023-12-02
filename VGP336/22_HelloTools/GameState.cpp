#include "GameState.h"
#include "AnimationChangeComponent.h"
#include "AnimationChangeInputService.h"

namespace
{
    bool CustomGameMake(const char* componentName, const rapidjson::Value& value, GameObject& gameObject)
    {
        if (strcmp(componentName, "AnimationChangeComponent") == 0)
        {
            AnimationChangeComponent* animationChangeComponent = gameObject.AddComponent<AnimationChangeComponent>();
            return true;
        }

        return false;
    }

    bool CustomServiceMake(const char* serviceName, const rapidjson::Value& value, GameWorld& gameWorld)
    {
        if (strcmp(serviceName, "AnimationChangeInputService") == 0)
        {
            AnimationChangeInputService* animationChangeInputService = gameWorld.AddService<AnimationChangeInputService>();
            return true;
        }

        return false;
    }
}

void GameState::Initialize()
{
    //mGameWorld.AddService<CameraService>();
    //mGameWorld.AddService<RenderService>();
    //mGameWorld.Initialize(100);
    //mGameWorld.CreateGameObject("../../Assets/Templates/fps_camera.json");
    GameObjectFactory::SetCustomMake(CustomGameMake);
    GameWorld::SetCustomServiceMake(CustomServiceMake);
    mGameWorld.LoadLevel(L"../../Assets/Templates/Levels/test_level.json");
}

void GameState::Terminate()
{
    mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
    /*auto input = InputSystem::Get();
    const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
    const float turnSpeed = 0.1f;
    const float modelTurnSpeed = 0.5f;

    if (input->IsKeyDown(KeyCode::W))
    {
        mCamera.Walk(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::S))
    {
        mCamera.Walk(-moveSpeed * deltaTime);
    }

    if (input->IsKeyDown(KeyCode::A))
    {
        mCamera.Strafe(-moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::D))
    {
        mCamera.Strafe(moveSpeed * deltaTime);
    }

    if (input->IsKeyDown(KeyCode::E))
    {
        mCamera.Rise(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::Q))
    {
        mCamera.Rise(-moveSpeed * deltaTime);
    }

    if (input->IsMouseDown(MouseButton::RBUTTON))
    {
        mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
        mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
    }*/

    // Replaced by the FPSCameraControllerComponent
    mGameWorld.Update(deltaTime);
}

void GameState::Render()
{
    mGameWorld.Render();
}

void GameState::DebugUI()
{
    mGameWorld.DebugUI();
}

void GameState::EditorUI()
{
    mGameWorld.EditorUI();
}
