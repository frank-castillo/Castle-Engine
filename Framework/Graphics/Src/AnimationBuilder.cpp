#include "Precompiled.h"
#include "AnimationBuilder.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::CEMath;

namespace
{
    template<class T>
    inline void PushKey(KeyFrames<T>& keyframes, const T& value, float time, EaseType easeType)
    {
        ASSERT(keyframes.empty() || keyframes.back().time < time, "AnimationBuilder -- Cannot add keyframe back in time");
        keyframes.emplace_back(value, time, easeType);
    }
}

AnimationBuilder& AnimationBuilder::AddPositionKey(const CEMath::Vector3& position, float time, EaseType easeType)
{
    PushKey(mWorkingCopy.mPositionKeys, position, time, easeType);
    mWorkingCopy.mDuration = Max(mWorkingCopy.mDuration, time);
    return *this;
}

AnimationBuilder& AnimationBuilder::AddRotationKey(const CEMath::Quaternion& rotation, float time, EaseType easeType)
{
    PushKey(mWorkingCopy.mRotationKeys, rotation, time, easeType);
    mWorkingCopy.mDuration = Max(mWorkingCopy.mDuration, time);
    return *this;
}

AnimationBuilder& AnimationBuilder::AddScaleKey(const CEMath::Vector3& scale, float time, EaseType easeType)
{
    PushKey(mWorkingCopy.mScaleKeys, scale, time, easeType);
    mWorkingCopy.mDuration = Max(mWorkingCopy.mDuration, time);
    return *this;
}

Animation AnimationBuilder::Build()
{
    ASSERT(!mWorkingCopy.mPositionKeys.empty() || !mWorkingCopy.mRotationKeys.empty() || !mWorkingCopy.mScaleKeys.empty(), "AnimationBuilder -- Animation has no keys");
    //ASSERT(mWorkingCopy.mDuration > 0.0f, "AnimationBuilder -- Animation has no duration");
    return std::move(mWorkingCopy);
}