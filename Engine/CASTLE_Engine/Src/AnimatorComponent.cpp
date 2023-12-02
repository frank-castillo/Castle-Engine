#include "Precompiled.h"

#include "AnimatorComponent.h"
#include "ModelComponent.h"
#include "GameObject.h"

using namespace CASTLEEngine;

void AnimatorComponent::Initialize()
{
    auto modelComponent = GetOwner().GetComponent<ModelComponent>();
    mAnimator.Initialize(modelComponent->GetModelId());
    mAnimator.PlayAnimation(0, true);
}

void AnimatorComponent::Update(float deltaTime)
{
    mAnimator.Update(deltaTime);
}

void AnimatorComponent::DebugUI()
{

}

bool AnimatorComponent::PlayAnimation(int index, bool looping)
{
    mAnimator.PlayAnimation(index, true);
    return true;
}
