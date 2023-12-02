#include <CASTLE_Engine/Inc/CASTLE_Engine.h>
#include "GameState.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::CEMath;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::Input;

float rotationX = 0.0f;
float rotationY = 0.0f;
float posZ = -1.0f;
float posX = 0.0f;

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
    CreateMesh();

    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
    posX = 0.0f;
    posZ = -4.0f;

    //mCamera.SetPosition({ 0.0f, 0.0f, -4.0f });

    mConstantBuffer.Initialize(sizeof(Matrix4));
    //mMeshBuffer.Initialize(mMesh);
    mMeshBuffer.Initialize(mMeshPX);
    mTextureId = TextureManager::Get()->LoadTexture(L"Textures/earth.jpg");

    mVertexShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx", VE_Position | VE_TexCoord);
    mPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");
}

void GameState::Terminate()
{
    mConstantBuffer.Terminate();
    mMeshBuffer.Terminate();
    mVertexShader.Terminate();
    mPixelShader.Terminate();
}

void GameState::Update(float deltaTime)
{
    // movement
    // physics
    // triggers
    // Results get sent to the rendering
    // Move camera position
    if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::UP))
    {
        rotationY += CEMath::Constants::kPiByTwo * 1 / 60;
    }
    else if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::DOWN))
    {
        rotationY -= CEMath::Constants::kPiByTwo * 1 / 60;
    }
    if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::RIGHT))
    {
        rotationX += CEMath::Constants::kPiByTwo * 1 / 60;
    }
    else if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::LEFT))
    {
        rotationX -= CEMath::Constants::kPiByTwo * 1 / 60;
    }

    if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::W))
    {
        posZ += CEMath::Constants::kPiByTwo * 1 / 60;
    }
    else if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::S))
    {
        posZ -= CEMath::Constants::kPiByTwo * 1 / 60;
    }

    if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::A))
    {
        posX -= CEMath::Constants::kPiByTwo * 1 / 60;
    }
    else if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::D))
    {
        posX += CEMath::Constants::kPiByTwo * 1 / 60;
    }


    if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::R))
    {
        posX = 0.0f;
        posZ = -2.0f;
        rotationX = 0.0f;
        rotationY = 0.0f;
    }
    mCamera.SetPosition({ posX,0.0f,posZ });
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
    TextureManager::Get()->BindPS(mTextureId, 0);

    mMeshBuffer.Render();
}

void GameState::DebugUI()
{
}

void GameState::CreateMesh()
{
    //mMesh = MeshBuilder::CreateCubePC(1.5f);
    //mMeshPX = MeshBuilder::CreateCubePX(1.5f);
    mMeshPX = MeshBuilder::CreateSpherePX(60, 60, 1);

    mCamera.SetLookAt({ 0.0f,0.0,0.0f });
    posX = 0.0f;
    posZ = -4.0f;
}