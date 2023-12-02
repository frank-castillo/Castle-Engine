#pragma once

#include "Common.h"

namespace CASTLEEngine::Graphics
{
    enum EaseType
    {
        Linear,
        EaseInQuad,
        EaseOutQuad,
        EaseInOutQuad
    };

    template<class T>
    struct Keyframe
    {
        Keyframe() = default;
        Keyframe(const T& k, float t, EaseType e = EaseType::Linear)
            : key(k),
            time(t),
            easeType (e)
        {

        }

        T key = T();
        float time = 0.0f;
        EaseType easeType = EaseType::Linear;
    };

    template<class T>
    using KeyFrames = std::vector<Keyframe<T>>;

    using PositionKeys = KeyFrames<CEMath::Vector3>;
    using RotationKeys = KeyFrames<CEMath::Quaternion>;
    using ScaleKeys = KeyFrames<CEMath::Vector3>;
}