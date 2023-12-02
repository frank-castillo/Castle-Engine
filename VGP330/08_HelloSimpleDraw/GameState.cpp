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
    mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
}

void GameState::Terminate()
{

}

void GameState::Update(float deltaTime)
{

}

void GameState::Render()
{
    if (mIsLine)
    {
        SimpleDraw::AddLine(mLinePos1, mLinePos2, mLineColor);
    }
    else
    {
        SimpleDraw::AddSphere(mSlices, mRings, mCircleRadius, mCircleColor);
    }

    SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
    ImGui::Begin("DebugDraw", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Checkbox("IsLine", &mIsLine);

    if (mIsLine)
    {
        ImGui::Begin("LineData", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::DragFloat3("Pos1", &mLinePos1.x, 0.01f);
        ImGui::DragFloat3("Pos2", &mLinePos2.x, 0.01f);
        ImGui::ColorEdit4("Color", &mLineColor.r);
        ImGui::End();
    }
    else
    {
        ImGui::Begin("SphereData", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::DragInt("Slices", &mSlices, 0.01f);
        ImGui::DragInt("Ring", &mRings, 0.01f);
        ImGui::DragFloat("Radius", &mCircleRadius, 0.01f);
        ImGui::ColorEdit4("Color", &mCircleColor.r);
        ImGui::End();
    }

    ImGui::End();
}