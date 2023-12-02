#include "AnimationChangeInputService.h"
#include "AnimationChangeComponent.h"
#include <Input/Inc/InputSystem.h>

using namespace CASTLEEngine;
using namespace CASTLEEngine::Input;

void AnimationChangeInputService::Initialize()
{
}

void AnimationChangeInputService::Terminate()
{
    mAnimationChangeComponents.clear();
}

void AnimationChangeInputService::Update(float deltaTime)
{
    auto input = InputSystem::Get();

    if(input->IsKeyPressed(KeyCode::ONE))
    {
        SetAllAnimationIndex(0);
    }
    else if (input->IsKeyPressed(KeyCode::TWO))
    {
        SetAllAnimationIndex(1);
    }
    else if (input->IsKeyPressed(KeyCode::THREE))
    {
        SetAllAnimationIndex(2);
    }
    else if (input->IsKeyPressed(KeyCode::FOUR))
    {
        SetAllAnimationIndex(3);
    }
    else if (input->IsKeyPressed(KeyCode::FIVE))
    {
        SetAllAnimationIndex(4);
    }
}

void AnimationChangeInputService::SetAllAnimationIndex(int index)
{
    for(auto animChangeComponent : mAnimationChangeComponents)
    {
        animChangeComponent->SetAnimation(index);
    }
}

void AnimationChangeInputService::Register(AnimationChangeComponent* animationChangeComponent)
{
    if(std::find(mAnimationChangeComponents.begin(), mAnimationChangeComponents.end(), animationChangeComponent) == mAnimationChangeComponents.end())
    {
        mAnimationChangeComponents.push_back(animationChangeComponent);
    }
}

void AnimationChangeInputService::Unregister(const AnimationChangeComponent* animationChangeComponent)
{
    auto iter = std::find(mAnimationChangeComponents.begin(), mAnimationChangeComponents.end(), animationChangeComponent);
    if(iter != mAnimationChangeComponents.end())
    {
        mAnimationChangeComponents.erase(iter);
    }
}
