#pragma once

#include "Keyframe.h"
#include "Transform.h"

namespace CASTLEEngine::Graphics
{
    class Animation
    {
    public:
        CEMath::Vector3 GetPosition(float time) const;
        CEMath::Quaternion GetRotation(float time) const;
        CEMath::Vector3 GetScale(float time) const;

        Transform GetTransform(float time) const;

        float GetDuration() const;

    private:
        friend class AnimationBuilder;
        friend class AnimationIO;

        PositionKeys mPositionKeys;
        RotationKeys mRotationKeys;
        ScaleKeys mScaleKeys;
        float mDuration;
    };
}