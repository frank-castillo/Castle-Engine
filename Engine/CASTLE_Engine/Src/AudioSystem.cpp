#include "Precompiled.h"
#include "AudioSystem.h"

#include <DirectXTK/Inc/Audio.h>

using namespace DirectX;
using namespace CASTLEEngine;

namespace
{
    std::unique_ptr<AudioSystem> sAudioSystem;
}

void AudioSystem::StaticInitialize()
{
    ASSERT(sAudioSystem == nullptr, "AudioSystem: has already been initialized!");
    sAudioSystem = std::make_unique<AudioSystem>();
    sAudioSystem->Initialize();
}

void AudioSystem::StaticTerminate()
{
    if (sAudioSystem != nullptr)
    {
        sAudioSystem->Terminate();
        sAudioSystem.reset();
    }
}

AudioSystem* AudioSystem::Get()
{
    return sAudioSystem.get();
}

AudioSystem::AudioSystem()
    : mAudioEngine(nullptr)
{

}

AudioSystem::~AudioSystem()
{
    ASSERT(mAudioEngine == nullptr, "AudioSystem: terminate was not called before delete!");
}

void AudioSystem::Initialize()
{
    ASSERT(mAudioEngine == nullptr, "AudioSystem: is already initialized");
    AUDIO_ENGINE_FLAGS flags = AudioEngine_Default;

#if defined(_DEBUG)
    flags = flags | AudioEngine_Debug;
#endif

    mAudioEngine = new DirectX::AudioEngine(flags);
}

void AudioSystem::Terminate()
{
    SafeDelete(mAudioEngine);
}

void AudioSystem::Update()
{
    if (mAudioEngine != nullptr && mAudioEngine->Update())
    {
        // No audio device is active
        if (mAudioEngine->IsCriticalError())
        {
            LOG("AudioSystem: CRITICAL ERROR, shutting down!");
            SafeDelete(mAudioEngine);
            //Terminate();
        }
    }
}