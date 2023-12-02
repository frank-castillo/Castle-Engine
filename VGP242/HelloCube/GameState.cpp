#include "GameState.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::CEMath;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::Input;

void GameState::OnCreateShape()
{
    mVertices.push_back({ Vector3(0.0f, 0.5f, 0.0f), Colors::Blue });
    mVertices.push_back({ Vector3(0.5f, -0.5f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.5f, -0.5f, 0.0f), Colors::Yellow });

    mVertices.push_back({ Vector3(-0.5f, -0.5f, 0.0f), Colors::MediumPurple });
    mVertices.push_back({ Vector3(-1.0f, 0.5f, 0.0f), Colors::AliceBlue });
    mVertices.push_back({ Vector3(0.0f, 0.5f, 0.0f), Colors::Aquamarine });

    mVertices.push_back({ Vector3(0.0f, 0.5f, 0.0f), Colors::MintCream });
    mVertices.push_back({ Vector3(1.0f, 0.5f, 0.0f), Colors::MistyRose });
    mVertices.push_back({ Vector3(0.5f, -0.5f, 0.0f), Colors::MediumOrchid });

    // float is 4 bytes
    // 4 * 3 * 9 = 108 bytes
    // There are redundant vertices!

    // We use indices, which are ints
    // We will only store the vectices that make up the shape. This is done to save memory
    // Indices will pick which one to render the shape
    // We only register unique vertices!!!!
    // We then use the indices to store a pseudo-reference (know which vertex to use) to those unique vertices
    // This saves some memory and avoids duplicate vertices

    /*std::vector<int> indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);

    indices.push_back(0);
    indices.push_back(4);
    indices.push_back(1);*/

    // We now have a list of indices that are just ints
    // Ints are 4 bytes
    // 4 * 3 * 5 = 60 bytes
    // 4 * 9 = 36 => these are the indices
    // Total we have => 96 bytes, way less that registering every index by itself

}

void Triangle::OnCreateShape()
{
    mVertices.push_back({ Vector3(-0.1f, -0.1f, 0.0f), Colors::Blue });
    mVertices.push_back({ Vector3(0.0f, -0.5f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.2f, -0.5f, 0.0f), Colors::Yellow });
}

void TriForce::OnCreateShape()
{
    mVertices.push_back({ Vector3(-0.1f, -0.1f, 0.0f), Colors::Blue });
    mVertices.push_back({ Vector3(0.0f, -0.5f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.2f, -0.5f, 0.0f), Colors::Yellow });

    mVertices.push_back({ Vector3(0.0f, 0.3f, 0.0f), Colors::Aqua });
    mVertices.push_back({ Vector3(0.1f, -0.1f, 0.0f), Colors::Azure });
    mVertices.push_back({ Vector3(-0.1f, -0.1f, 0.0f), Colors::Yellow });

    mVertices.push_back({ Vector3(0.1f, -0.1f, 0.0f), Colors::Beige });
    mVertices.push_back({ Vector3(0.2f, -0.5f, 0.0f), Colors::Coral });
    mVertices.push_back({ Vector3(0.0f, -0.5f, 0.0f), Colors::MintCream });
}

void Heart::OnCreateShape()
{
    mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::PaleVioletRed });
    mVertices.push_back({ Vector3(0.0f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.1f, 0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::PaleVioletRed });
    mVertices.push_back({ Vector3(-0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.0f, 0.2f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::PaleVioletRed });
    mVertices.push_back({ Vector3(0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.1f, -0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::PaleVioletRed });
    mVertices.push_back({ Vector3(-0.1f, -0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.1f, 0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::PaleVioletRed });
    mVertices.push_back({ Vector3(0.1f, -0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.0f, -0.2f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(0.0f, 0.0f, 0.0f), Colors::PaleVioletRed });
    mVertices.push_back({ Vector3(0.0f, -0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.1f, -0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(0.0f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.1f, 0.3f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.1f, 0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(0.0f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.1f, 0.3f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.1f, 0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(0.1f, 0.3f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.2f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.1f, 0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.2f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.2f, 0.0f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.2f, 0.0f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.1f, -0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(0.0f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.1f, 0.3f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(-0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.2f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.1f, 0.3f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(-0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.2f, 0.0f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.2f, 0.2f, 0.0f), Colors::Red });

    mVertices.push_back({ Vector3(-0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.1f, -0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.2f, 0.0f, 0.0f), Colors::Red });
}

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

    mCamera.SetPosition({ 0.0f, 1.0f, -2.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    OnCreateShape();

    mConstantBuffer.Initialize(sizeof(Matrix4));
    mMeshBuffer.Initialize(mVertices.data(), sizeof(Vertex), mVertices.size());
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

void Cube::OnCreateShape()
{
    // Front
    mVertices.push_back({ Vector3(-0.5f, 0.5f, -0.5f), Colors::Blue });
    mVertices.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Blue });
    mVertices.push_back({ Vector3(-0.5f, -0.5f, -0.5f), Colors::Blue });

    mVertices.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Blue });
    mVertices.push_back({ Vector3(0.5f, -0.5f, -0.5f), Colors::Blue });
    mVertices.push_back({ Vector3(-0.5f, -0.5f, -0.5f), Colors::Blue });

    // Back
    mVertices.push_back({ Vector3(-0.5f, -0.5f, 0.5f), Colors::Yellow });
    mVertices.push_back({ Vector3(0.5f, 0.5f, 0.5f), Colors::Yellow });
    mVertices.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Yellow });

    mVertices.push_back({ Vector3(-0.5f, -0.5f, 0.5f), Colors::Yellow });
    mVertices.push_back({ Vector3(0.5f, -0.5f, 0.5f), Colors::Yellow });
    mVertices.push_back({ Vector3(0.5f, 0.5f, 0.5f), Colors::Yellow });

    // Right
    mVertices.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, 0.5f, 0.5f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, -0.5f, -0.5f), Colors::Red });

    mVertices.push_back({ Vector3(0.5f, 0.5f, 0.5f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, -0.5f, 0.5f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, -0.5f, -0.5f), Colors::Red });

    // Left
    mVertices.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Aqua });
    mVertices.push_back({ Vector3(-0.5f, 0.5f, -0.5f), Colors::Aqua });
    mVertices.push_back({ Vector3(-0.5f, -0.5f, -0.5f), Colors::Aqua });

    mVertices.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Aqua });
    mVertices.push_back({ Vector3(-0.5f, -0.5f, -0.5f), Colors::Aqua });
    mVertices.push_back({ Vector3(-0.5f, -0.5f, 0.5f), Colors::Aqua });

    // Top
    mVertices.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Azure });
    mVertices.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Azure });
    mVertices.push_back({ Vector3(-0.5f, 0.5f, -0.5f), Colors::Azure });

    mVertices.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Azure });
    mVertices.push_back({ Vector3(0.5f, 0.5f, 0.5f), Colors::Azure });
    mVertices.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Azure });

    // Bottom
    mVertices.push_back({ Vector3(-0.5f, -0.5f, -0.5f), Colors::Coral });
    mVertices.push_back({ Vector3(0.5f, -0.5f, -0.5f), Colors::Coral });
    mVertices.push_back({ Vector3(0.5f, -0.5f, 0.5f), Colors::Coral });

    mVertices.push_back({ Vector3(-0.5f, -0.5f, -0.5f), Colors::Coral });
    mVertices.push_back({ Vector3(0.5f, -0.5f, 0.5f), Colors::Coral });
    mVertices.push_back({ Vector3(-0.5f, -0.5f, 0.5f), Colors::Coral });
}