#include "StandardFogState.h"
#include "Input/Inc/InputSystem.h"

void StandardFogState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 1.0f, -6.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    mDirectionalLight.direction = Normalize({ 1.0f,-1.0f, 1.0f });
    mDirectionalLight.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
    mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

    Mesh ground = MeshBuilder::CreatePlane(20, 20, 1.0f);
    mGround.meshBuffer.Initialize(ground);
    mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/earth.jpg");
    mGround.material.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.specular = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.power = { 1.0f };

    Model character;
    ModelIO::LoadModel("../../Assets/Models/Mutant.model", character);
    ModelIO::LoadMaterial("../../Assets/Models/Mutant.material", character);
    mCharacter = CreateRenderGroup(character);

    mShadowEffect.Initialize();
    mShadowEffect.SetDirectionalLight(mDirectionalLight);

    mStandardFogEffect.Initialize(L"../../Assets/Shaders/StandardFog.fx");
    mStandardFogEffect.SetCamera(mCamera);
    mStandardFogEffect.SetDirectionalLight(mDirectionalLight);
    mStandardFogEffect.SetLightCamera(mShadowEffect.GetLightCamera());
    mStandardFogEffect.SetShadowMap(&mShadowEffect.GetDepthMap());

    mAlphaBlendState.Initialize(BlendState::Mode::AlphaBlend);
}

void StandardFogState::Terminate()
{
    mAlphaBlendState.Terminate();
    mStandardFogEffect.Terminate();
    mShadowEffect.Terminate();
    CleanUpRenderGroup(mCharacter);
    mGround.Terminate();
}

void StandardFogState::Update(float deltaTime)
{
    auto input = InputSystem::Get();
    const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
    const float turnSpeed = 0.1f;

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
}

void StandardFogState::Render()
{
    mAlphaBlendState.Set();
    {
        mShadowEffect.Begin();
        DrawRenderGroup(mShadowEffect, mCharacter);
        mShadowEffect.End();

        mStandardFogEffect.Begin();
        DrawRenderGroup(mStandardFogEffect, mCharacter);
        mStandardFogEffect.Render(mGround);
        mStandardFogEffect.End();
    }
    BlendState::ClearState();
}

void StandardFogState::DebugUI()
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

    ImGui::Separator();

    mStandardFogEffect.DebugUI();
    mShadowEffect.DebugUI();

    ImGui::End();
}