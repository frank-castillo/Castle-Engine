#include "Precompiled.h"

#include "TimeUtil.h"

float CASTLEEngine::Core::TimeUtil::GetTime()
{
    //Gets the difference since the start time
    static const auto startTime = std::chrono::high_resolution_clock::now();
    const auto currentTime = std::chrono::high_resolution_clock::now();
    const auto miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
    return miliseconds / 1000.0f;
}

float CASTLEEngine::Core::TimeUtil::GetDeltaTime()
{
    //Gets the difference since the last time we checked
    static auto lastCallTime = std::chrono::high_resolution_clock::now();
    const auto currentTime = std::chrono::high_resolution_clock::now();
    const auto miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastCallTime).count();
    lastCallTime = currentTime;
    return miliseconds / 1000.0f;
}