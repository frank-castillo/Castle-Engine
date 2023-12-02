#pragma once
#include "Animation.h"

namespace CASTLEEngine::Graphics
{
    class AnimationBuilder
    {
    public:
        AnimationBuilder& AddPositionKey(const CEMath::Vector3& position, float time, EaseType easeType = EaseType::Linear);
        AnimationBuilder& AddRotationKey(const CEMath::Quaternion& rotation, float time, EaseType easeType = EaseType::Linear);
        AnimationBuilder& AddScaleKey(const CEMath::Vector3& scale, float time, EaseType easeType = EaseType::Linear);

        // Forces you to have a variable to which aply this, you can't just create an instance without a container
        [[nodiscard]] Animation Build();

    private:
        Animation mWorkingCopy;
    };
}