#pragma once

#include "Colors.h"

namespace CASTLEEngine::Graphics
{
    struct DirectionalLight
    {
        CEMath::Vector3 direction = CEMath::Vector3::Zero;
        float padding = 0.0f;
        Color ambient = Colors::White;
        Color diffuse = Colors::White;
        Color specular = Colors::White;
    };
}