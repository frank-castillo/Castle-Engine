#include "GameState.h"
#include "Input/Inc/InputSystem.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::Input;

void GameState::Initialize()
{
    GraphicsSystem::Get()->SetClearColor(CASTLEEngine::Colors::Black);
}

void GameState::Terminate()
{
}

void GameState::Update(float deltaTime)
{
    auto inputSystem = InputSystem::Get();

    if (inputSystem->IsKeyPressed(KeyCode::NUMPAD1))
    {
        GraphicsSystem::Get()->SetClearColor(CASTLEEngine::Colors::Red);
    }
    else if (inputSystem->IsKeyPressed(KeyCode::NUMPAD2))
    {
        GraphicsSystem::Get()->SetClearColor(CASTLEEngine::Colors::Green);
    }
}

void GameState::Render()
{

}