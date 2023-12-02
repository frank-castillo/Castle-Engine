#include "AnimationChangeComponent.h"
#include <CASTLE_Engine/Inc/GameObject.h>
#include <CASTLE_Engine/Inc/GameWorld.h>
#include <CASTLE_Engine/Inc/AnimatorComponent.h>
#include "AnimationChangeInputService.h"

void AnimationChangeComponent::Initialize()
{
    mAnimatorComponent = GetOwner().GetComponent<AnimatorComponent>();

    auto animChangeInputService = GetOwner().GetWorld().GetService<AnimationChangeInputService>();
    animChangeInputService->Register(this);
}

void AnimationChangeComponent::Terminate()
{
    auto animChangeInputService = GetOwner().GetWorld().GetService<AnimationChangeInputService>();
    animChangeInputService->Unregister(this);
    mAnimatorComponent = nullptr;
}

void AnimationChangeComponent::Update(float deltaTime)
{
}

void AnimationChangeComponent::SetAnimation(int index)
{
    mAnimatorComponent->GetAnimator().PlayAnimation(index, true);
}
