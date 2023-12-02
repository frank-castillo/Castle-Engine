#pragma once
#include <CASTLE_Engine/Inc/Component.h>
#include "TypeIds.h"

namespace CASTLEEngine
{
    class AnimatorComponent;
}

class AnimationChangeComponent final : public CASTLEEngine::Component
{
public:
    SET_TYPE_ID(CustomComponentId::AnimationChangeComponentId);

    void Initialize() override;
    void Terminate() override;

    void Update(float deltaTime) override;

    void SetAnimation(int index);

private:
    CASTLEEngine::AnimatorComponent* mAnimatorComponent;
};