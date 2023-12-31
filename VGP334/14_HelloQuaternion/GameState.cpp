#include "GameState.h"
#include "Input/Inc/InputSystem.h"

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    mDirectionalLight.direction = Normalize({ 1.0f,-1.0f, 1.0f });
    mDirectionalLight.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
    mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

    Mesh ground = MeshBuilder::CreatePlane(20, 20, 1.0f);
    mGround.meshBuffer.Initialize(ground);
    mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/misc/concrete.jpg");
    mGround.material.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.specular = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.power = {1.0f};
    mGround.transform.position.y = -1.5f;

    Mesh sphere = MeshBuilder::CreateSphere(20, 20, 1.0f);
    mSphere.meshBuffer.Initialize(sphere);
    mSphere.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/planets/mars.jpg");
    mSphere.material.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mSphere.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    mSphere.material.specular = { 0.8f, 0.8f, 0.8f, 1.0f };
    mSphere.material.power = { 1.0f };
    mSphere.transform.position.y = 0.0f;

    mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandardEffect.SetCamera(mCamera);
    mStandardEffect.SetDirectionalLight(mDirectionalLight);
}

void GameState::Terminate()
{
    mStandardEffect.Terminate();
    mSphere.Terminate();
    mGround.Terminate();
}

void GameState::Update(float deltaTime)
{
    auto input = InputSystem::Get();
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
    }

    if (input->IsKeyDown(KeyCode::UP))
    {
        mPitch += modelTurnSpeed * deltaTime;
    }
    else if (input->IsKeyDown(KeyCode::DOWN))
    {
        mPitch -= modelTurnSpeed * deltaTime;
    }

    if (input->IsKeyDown(KeyCode::LEFT))
    {
        mYaw += modelTurnSpeed * deltaTime;
    }
    else if (input->IsKeyDown(KeyCode::RIGHT))
    {
        mYaw -= modelTurnSpeed * deltaTime;
    }

    if (input->IsKeyDown(KeyCode::NUMPAD1))
    {
        mRoll += modelTurnSpeed * deltaTime;
    }
    else if (input->IsKeyDown(KeyCode::NUMPAD2))
    {
        mRoll -= modelTurnSpeed * deltaTime;
    }

    //mRoll += turnSpeed * deltaTime;
    mSphere.transform.rotation = Quaternion::CreateFromYawPitchRoll(mYaw, mPitch, mRoll);
}

void GameState::Render()
{
    mStandardEffect.Begin();
        mStandardEffect.Render(mGround);
        mStandardEffect.Render(mSphere);
    mStandardEffect.End();
}

void GameState::DebugUI()
{
    ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Separator();

    if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::DragFloat3("Direction##Light", &mDirectionalLight.direction.x, 0.01f, -1.0f, 1.0f))
        {
            mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
        }

        ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
        ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
        ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
    }

    ImGui::DragFloat("Yaw##", &mYaw, 0.1f);
    ImGui::DragFloat("Roll##", &mRoll, 0.1f);
    ImGui::DragFloat("Pitch##", &mPitch, 0.1f);

    ImGui::Separator();

    mStandardEffect.DebugUI();

    ImGui::End();
}