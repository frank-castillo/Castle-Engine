#pragma once

#include "Common.h"

namespace CASTLEEngine::Graphics
{
    struct Transform
    {
        CEMath::Vector3 position = CEMath::Vector3::Zero;
        CEMath::Quaternion rotation = CEMath::Quaternion::Identity();
        CEMath::Vector3 scale = CEMath::Vector3::One;

        Transform() = default;

        Transform(const CEMath::Matrix4& m)
        {
            position = CEMath::GetTranslation(m);
            rotation = CEMath::Quaternion::CreateFromRotationMatrix(m);
            scale = CEMath::GetScale(m);
        }

        CEMath::Matrix4 GetMatrix4() const
        {
            return
            {
                CEMath::Matrix4::Scaling(scale) *
                CEMath::Matrix4::MatrixRotationQuaternion(rotation) *
                CEMath::Matrix4::Translation(position)
            };
        }
    };
}