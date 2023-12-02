#include "GameState.h"
#include "Input/Inc/InputSystem.h"

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 1.0f, -20.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    mDirectionalLight.direction = Normalize({ 1.0f,-1.0f, 1.0f });
    mDirectionalLight.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
    mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

    Mesh ball = MeshBuilder::CreateSphere(30, 30, 1.0f);
    mBall.meshBuffer.Initialize(ball);
    mBall.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/misc/basketball.jpg");
    mBall.material.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mBall.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    mBall.material.specular = { 0.8f, 0.8f, 0.8f, 1.0f };
    mBall.material.power = { 1.0f };
    mBall.transform.position.y = 10.0f;

    mSphereCollisionShape.Initialize(1.0f);
    mBallRigidBody.Initialize(mBall.transform, mSphereCollisionShape, 5.0f);

    Mesh ground = MeshBuilder::CreatePlane(20, 20, 1.0f);
    mGround.meshBuffer.Initialize(ground);
    mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/misc/concrete.jpg");
    mGround.material.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.specular = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.power = { 1.0f };
    mGround.transform.position.y = 0.0f;

    mBoxCollisionShape.Initialize({ 10.0f, 0.005, 10.0f });
    mGroundRigidBody.Initialize(mGround.transform, mBoxCollisionShape);

    mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandardEffect.SetCamera(mCamera);
    mStandardEffect.SetDirectionalLight(mDirectionalLight);

    ParticleSystemInfo info;
    info.lifeTime = 999999999999.0f;
    info.maxParticles = 50;
    info.minParticleSpeed = 5.0f;
    info.maxParticleSpeed = 10.0f;
    info.minParticlesPerEmit = 1;
    info.maxParticlesPerEmit = 5;
    info.minSpawnAngle = -CEMath::Constants::kPiByTwo * 0.5f;;
    info.maxSpawnAngle = CEMath::Constants::kPiByTwo * 0.5f;
    info.minTimeBetweenParticles = 0.001f;
    info.maxTimeBetweenParticles = 0.02f;
    // Particle
    info.particleInfo.lifeTime = 2.0f;
    info.particleInfo.startScale = { 1.0f, 1.0f, 1.0f };
    info.particleInfo.endScale = { 0.2f, 0.2f, 0.2f };
    info.particleInfo.startColor = Colors::Blue;
    info.particleInfo.endColor = Colors::Red;
    mParticleSystem.Initialize(info, Vector3::Zero, Vector3::YAxis);
}

void GameState::Terminate()
{
    mParticleSystem.Terminate();
    mStandardEffect.Terminate();

    mGroundRigidBody.Terminate();
    mBoxCollisionShape.Terminate();
    mGround.Terminate();

    mBallRigidBody.Terminate();
    mSphereCollisionShape.Terminate();
    mBall.Terminate();
}

int gAnimationIndex = 0;
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

    mParticleSystem.Update(deltaTime);
}

void GameState::Render()
{
    mStandardEffect.Begin();
    mParticleSystem.Render();
    mStandardEffect.Render(mBall);
    mStandardEffect.Render(mGround);
    mStandardEffect.End();

    //SimpleDraw::AddGroundPlane(20.0f, Colors::White);
    SimpleDraw::Render(mCamera);
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

    ImGui::Separator();

    mStandardEffect.DebugUI();
    PhysicsWorld::Get()->DebugUI();

    ImGui::End();
}