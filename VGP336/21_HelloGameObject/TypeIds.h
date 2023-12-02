#pragma once

#include <CASTLE_Engine/Inc/TypeIds.h>

enum class CustomComponentId
{
    AnimationChangeComponentId = static_cast<uint32_t>(CASTLEEngine::ComponentId::Count)
    // Any component added after this will follow the ordering from the highest value on Count
};

enum class CustomServiceId
{
    AnimationChangeInputServiceId = static_cast<uint32_t>(CASTLEEngine::ServiceId::Count)
};