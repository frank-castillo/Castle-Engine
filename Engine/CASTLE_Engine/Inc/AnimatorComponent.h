#pragma once

#include "Component.h"

namespace CASTLEEngine
{
    class AnimatorComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::AnimatorComponent);

        void Initialize() override;
        void Update(float deltaTime) override;
        void DebugUI() override;

        bool PlayAnimation(int index, bool looping);

        Graphics::Animator& GetAnimator() { return mAnimator; }
        const Graphics::Animator& GetAnimator() const { return mAnimator; }

    private:
        Graphics::Animator mAnimator;
    };
}
