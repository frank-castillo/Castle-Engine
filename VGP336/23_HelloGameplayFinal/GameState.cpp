#include "GameState.h"
#include "ThirdPersonCameraComponent.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::CEMath;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::Input;
using namespace CASTLEEngine::Physics;

namespace
{
    bool CustomGameMake(const char* componentName, const rapidjson::Value& value, GameObject& gameObject)
    {
        if (strcmp(componentName, "ThirdPersonCameraComponent") == 0)
        {
            ThirdPersonCameraComponent* thirdPersonCameraComponent = gameObject.AddComponent<ThirdPersonCameraComponent>();
            /*if (value.HasMember("MoveSpeed"))
            {
                const float moveSpeed = value["MoveSpeed"].GetFloat();
                thirdPersonCameraComponent->SetMoveSpeed(moveSpeed);
            }
            if (value.HasMember("TurnSpeed"))
            {
                const float turnSpeed = value["TurnSpeed"].GetFloat();
                thirdPersonCameraComponent->SetTurnSpeed(turnSpeed);
            }*/
            return true;
        }

        return false;
    }

    bool CustomServiceMake(const char* serviceName, const rapidjson::Value& value, GameWorld& gameWorld)
    {
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
