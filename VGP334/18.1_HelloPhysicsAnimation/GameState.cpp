#include "GameState.h"
#include "Input/Inc/InputSystem.h"

using namespace CASTLEEngine::CEMath;
using namespace CASTLEEngine::Input;

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 1.0f, -10.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
    
    mDirectionalLight.direction = CEMath::Normalize({ 1.0f, -1.0f, 1.0f });
    mDirectionalLight.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
    mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

    //Mesh ball = MeshBuilder::CreateSphere(30, 30, 1.0f);
    //mBall.meshBuffer.Initialize(ball);
    //mBall.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/misc/basketball.jpg");
    //mBall.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
    //mBall.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    //mBall.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
    //mBall.material.power = 10.0f;
    //mBall.transform.position.y = 10.0f;

    //mSphereCollisionShape.Initialize(1.0f);
    //mBallRigidBody.Initialize(mBall.transform, mSphereCollisionShape, 5.0f);

    Mesh ground = MeshBuilder::CreatePlane(20, 20, 1.0f);
    mGround.meshBuffer.Initialize(ground);
    mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/misc/concrete.jpg");
    mGround.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
    mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
    mGround.material.power = 10.0f;

    //mGroundCollisionShape.Initialize({ 10.0f, 0.005f, 10.0f });
    //mGroundRigidBody.Initialize(mGround.transform, mGroundCollisionShape);

    mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandardEffect.SetCamera(mCamera);
    mStandardEffect.SetDirectionalLight(mDirectionalLight);

    mParticleEffect.Initialize();
    mParticleEffect.SetCamera(mCamera);

    // particle system
    ParticleSystemInfo info;
    info.lifeTime = 999999999999.0f;
    info.maxParticles = 50;
    info.minParticleSpeed = 2.0f;
    info.maxParticleSpeed = 5.0f;
    info.minParticlesPerEmit = 1;
    info.maxParticlesPerEmit = 2;
    info.minSpawnAngle = -CEMath::Constants::kPiByTwo * 0.25f;
    info.maxSpawnAngle = CEMath::Constants::kPiByTwo * 0.25f;
    info.minTimeBetweenParticles = 0.01f;
    info.maxTimeBetweenParticles = 0.02f;
    // particle
    info.particleInfo.lifetime = 1.0f;
    info.particleInfo.startScale = {1.0f, 1.0f, 1.0f};
    info.particleInfo.endScale = {0.01f, 0.01f, 0.01f};
    info.particleInfo.startColor = Colors::OrangeRed;
    info.particleInfo.startColor.a = 0.8f;
    info.particleInfo.endColor = Colors::LightGoldenrodYellow;
    info.particleInfo.endColor.a = 0.0f;
    mParticleSystem.Initialize(info, Vector3::Zero, Vector3::YAxis);
}
void GameState::Terminate()
{
    mParticleSystem.Terminate();

    mParticleEffect.Terminate();
    mStandardEffect.Terminate();

    mGroundRigidBody.Terminate();
    mGroundCollisionShape.Terminate();
    mGround.Terminate();

    mBallRigidBody.Terminate();
    mSphereCollisionShape.Terminate();
    mBall.Terminate();

}

void GameState::Update(float deltaTime)
{
    // movement
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

    if (input->IsKeyDown(KeyCode::D))
    {
        mCamera.Strafe(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::A))
    {
        mCamera.Strafe(-moveSpeed * deltaTime);
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
        //mStandardEffect.Render(mBall);
        mStandardEffect.Render(mGround);
    mStandardEffect.End();

    mParticleEffect.Begin();
    mParticleSystem.Render(mParticleEffect);
    mParticleEffect.End();
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
    mStandardEffect.DebugUI();

    PhysicsWorld::Get()->DebugUI();

    ImGui::End();

    SimpleDraw::Render(mCamera);
}