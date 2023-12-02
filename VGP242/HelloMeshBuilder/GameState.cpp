#include <CASTLE_Engine/Inc/CASTLE_Engine.h>
#include "GameState.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::CEMath;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::Input;

void GameState::Initialize()
{
    // NDC - Normalized Device Coordinate
   //
   //            +-----------------+
   //           /                 /|
   //     1.0  +-----------------+ |
   //          |        ^        | |
   //          |        |        | |
   //          | <------+------> | |
   //          |        |        | | 1.0
   //          |        v        |/
   //    -1.0  +-----------------+ 0.0
   //      -1.0               1.0
   //

    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
    mCamera.SetPosition({ 0.0f, 0.0f, -4.0f });

    CreateMesh();

    mConstantBuffer.Initialize(sizeof(Matrix4));
    mMeshBuffer.Initialize(mMesh);
    mVertexShader.Initialize(L"../../Assets/Shaders/DoTransform.fx", VE_Position | VE_Color);
    mPixelShader.Initialize(L"../../Assets/Shaders/DoTransform.fx");
}

void GameState::Terminate()
{
    mConstantBuffer.Terminate();
    mMeshBuffer.Terminate();
    mVertexShader.Terminate();
    mPixelShader.Terminate();
}

float rotationX = 0.0f;
float rotationY = 0.0f;

void GameState::Update(float deltaTime)
{
    // movement
    // physics
    // triggers
    // Results get sent to the rendering
    // Move camera position
    mRunningTime += deltaTime;

    if (InputSystem::Get()->IsKeyDown(Input::KeyCode::UP))
    {
        rotationY += 5.0f * deltaTime;
    }
    else if (InputSystem::Get()->IsKeyDown(Input::KeyCode::DOWN))
    {
        rotationY -= 5.0f * deltaTime;
    }

    if (InputSystem::Get()->IsKeyDown(Input::KeyCode::LEFT))
    {
        rotationX += 5.0f * deltaTime;
    }
    if (InputSystem::Get()->IsKeyDown(Input::KeyCode::RIGHT))
    {
        rotationX -= 5.0f * deltaTime;
    }
}

void GameState::Render()
{
    mVertexShader.Bind();
    mPixelShader.Bind();

    Matrix4 cubeWorldRotY = Matrix4::RotationX(rotationY);
    Matrix4 cubeWorldRotX = Matrix4::RotationY(rotationX);
    Matrix4 cubeWorldTrans = Matrix4::Identity;
    Matrix4 view = mCamera.GetViewMatrix();
    Matrix4 proj = mCamera.GetProjectionMatrix();
    Matrix4 wvp = Transpose(cubeWorldRotX * cubeWorldRotY * view * proj);
    mConstantBuffer.Update(&wvp);
    mConstantBuffer.BindVS(0);

    mMeshBuffer.Render();
}

void GameState::DebugUI()
{
}

void GameState::CreateMesh()
{
    mMesh = MeshBuilder::CreateCubePC(1.5f);
}