#pragma once

#include "Common.h"

namespace CASTLEEngine::Graphics
{
    struct Bone
    {
        std::string name;
        int index = -1;

        Bone* parent = nullptr;
        int parentIndex = -1;

        std::vector<Bone*> children;
        std::vector<int> childrenIndices;

        CEMath::Matrix4 toParentTransform;
        CEMath::Matrix4 offsetTransform;
    };
}