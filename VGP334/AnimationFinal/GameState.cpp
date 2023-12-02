#include "GameState.h"
#include "Input/Inc/InputSystem.h"

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    mDirectionalLight.direction = Normalize({ 1.0f,-1.0f, 1.0f });
    mDirectionalLight.ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
    mDirectionalLight.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
    mDirectionalLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };

    Mesh ground = MeshBuilder::CreatePlane(20, 20, 1.0f);
    mGround.meshBuffer.Initialize(ground);
    mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/misc/concrete.jpg");
    mGround.material.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.specular = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.power = { 1.0f };

    auto mm = ModelManager::Get();
    mCharacterModelId = ModelManager::Get()->LoadModel(L"../../Assets/Models/Archer/ArcherIdle.model");
    mm->AddAnimation(mCharacterModelId, L"../../Assets/Models/Archer/Anims/ArcherForward.fbx");
    mm->AddAnimation(mCharacterModelId, L"../../Assets/Models/Archer/Anims/ArcherBackward.fbx");
    mm->AddAnimation(mCharacterModelId, L"../../Assets/Models/Archer/Anims/ArcherLeft.fbx");
    mm->AddAnimation(mCharacterModelId, L"../../Assets/Models/Archer/Anims/ArcherRight.fbx");
    //mCharacterAnimator.Initialize(mCharacterModelId);
    mCharacterAnimatorTree.Initialize(mCharacterModelId);
    mCharacter = CreateRenderGroup(mCharacterModelId, &mCharacterAnimator);
    //mCharacterAnimator.PlayAnimation(0, true);

    mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandardEffect.SetCamera(mCamera);
    mStandardEffect.SetDirectionalLight(mDirectionalLight);

    mDrawSkeleton = false;
}

void GameState::Terminate()
{
    mStandardEffect.Terminate();
    CleanUpRenderGroup(mCharacter);
    mGround.Terminate();
}

int gAnimationIndex = 0;
void GameState::Update(float deltaTime)
{
    //mCharacterAnimator.Update(deltaTime);
    mCharacterAnimatorTree.Update(deltaTime);

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

    if (input->IsKeyPressed(KeyCode::UP))
    {
        int animCount = mCharacterAnimator.GetAnimationCount();
        gAnimationIndex = (gAnimationIndex + 1) % animCount;
        mCharacterAnimator.PlayAnimation(gAnimationIndex, true, 1.0f);
    }
    else if (input->IsKeyPressed(KeyCode::DOWN))
    {
        int animCount = mCharacterAnimator.GetAnimationCount();
        gAnimationIndex = (gAnimationIndex - 1);
        if (gAnimationIndex < 0)
        {
            gAnimationIndex = animCount - 1;
        }
        mCharacterAnimator.PlayAnimation(gAnimationIndex, true, 1.0f);
    }
}

void GameState::Render()
{
    mStandardEffect.Begin();
    mStandardEffect.Render(mGround);
    if (mDrawSkeleton)
    {
        AnimationUtil::BoneTransforms boneTransforms;
        //AnimationUtil::ComputeBoneTransform(mCharacterModelId, boneTransforms, &mCharacterAnimator);
        AnimationUtil::ComputeBoneTransform(mCharacterModelId, boneTransforms, &mCharacterAnimatorTree);
        AnimationUtil::DrawSkeleton(mCharacterModelId, boneTransforms);
    }
    else
    {
        DrawRenderGroup(mStandardEffect, mCharacter);
    }

    mStandardEffect.End();
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

    ImGui::Separator();

    ImGui::Checkbox("Draw Skeleton Lines", &mDrawSkeleton);

    ImGui::Separator();

    // Create a layout for the 5-axis drag matrix
    ImGui::Columns(2);
    ImGui::Text("X");
    ImGui::NextColumn();
    ImGui::Text("Y");
    ImGui::NextColumn();
    ImGui::Separator();

    // Example code for the X axis
    ImGui::Text("X Axis:");
    static float xAxisValue = 0.0f;
    ImGui::DragFloat("##XAxis", &xAxisValue, 0.1f);
    ImGui::NextColumn();

    // Example code for the Y axis
    ImGui::Text("Y Axis:");
    static float yAxisValue = 0.0f;
    ImGui::DragFloat("##YAxis", &yAxisValue, 0.1f);
    ImGui::NextColumn();

    // ... Repeat the above code for the remaining axes

    ImGui::Columns(1); // Reset columns

    // Example code for modifying an int parameter based on the 5-axis drag matrix
    static int selectedAxis = 0;
    static int intValue = 0;

    ImGui::Text("Selected Axis: %d", selectedAxis);
    ImGui::SliderInt("Int Value", &intValue, -10, 10);

    ImGui::End();
}