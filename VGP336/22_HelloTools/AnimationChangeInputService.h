#pragma once

#include <CASTLE_Engine/Inc/Service.h>
#include "TypeIds.h"

class AnimationChangeComponent;

class AnimationChangeInputService final : public CASTLEEngine::Service
{
public:
    SET_TYPE_ID(CustomServiceId::AnimationChangeInputServiceId);

    void Initialize() override;
    void Terminate() override;

    void Update(float deltaTime) override;

private:
    void SetAllAnimationIndex(int index);

    using AnimationChangeComponents = std::vector<AnimationChangeComponent*>;
    AnimationChangeComponents mAnimationChangeComponents;

    friend class AnimationChangeComponent;
    void Register(AnimationChangeComponent* animationChangeComponent);
    void Unregister(const AnimationChangeComponent* animationChangeComponent);
};