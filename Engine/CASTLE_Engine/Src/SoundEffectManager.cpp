#include "Precompiled.h"
#include "SoundEffectManager.h"

#include "AudioSystem.h"
#include <DirectXTK/Inc/Audio.h>

using namespace DirectX;
using namespace CASTLEEngine;

namespace
{
    std::unique_ptr<SoundEffectManager> sSoundEffectManager;
}

void SoundEffectManager::StaticInitialize(const std::filesystem::path& root)
{
    ASSERT(sSoundEffectManager == nullptr, "SoundEffectManager: is already initialized!");
    sSoundEffectManager = std::make_unique<SoundEffectManager>();
    sSoundEffectManager->SetRootPath(root);
}

void SoundEffectManager::StaticTerminate()
{
    if (sSoundEffectManager != nullptr)
    {
        sSoundEffectManager->Clear();
        sSoundEffectManager.reset();
    }
}

SoundEffectManager* SoundEffectManager::Get()
{
    return sSoundEffectManager.get();
}

SoundEffectManager::SoundEffectManager()
{

}

SoundEffectManager::~SoundEffectManager()
{
    ASSERT(mInventory.empty(), "SoundEffectManager: Clear must be called before deletion");
}

void SoundEffectManager::SetRootPath(const std::filesystem::path& path)
{
    mRoot = path;
}

SoundId SoundEffectManager::Load(const std::filesystem::path& fileName)
{
    std::filesystem::path fullPath = mRoot / fileName;
    auto soundId = std::filesystem::hash_value(fileName);
    auto [iter, success] = mInventory.insert({ soundId, nullptr });

    if (success)
    {
        auto& soundEventPtr = iter->second;
        soundEventPtr = std::make_unique<Entry>();
        soundEventPtr->effect = std::make_unique<SoundEffect>(AudioSystem::Get()->mAudioEngine, fullPath.wstring().c_str());
        soundEventPtr->instance = soundEventPtr->effect->CreateInstance();
    }

    return soundId;
}

void SoundEffectManager::Clear()
{
    AudioSystem::Get()->mAudioEngine->Suspend();

    for (auto& item : mInventory)
    {
        if (item.second)
        {
            item.second->instance->Stop();
            item.second->instance.reset();
            item.second->effect.reset();
            item.second.reset();
        }
    }

    mInventory.clear();
}

void SoundEffectManager::Play(SoundId id, bool loop /*= false*/)
{
    auto iter = mInventory.find(id);
    if (iter != mInventory.end())
    {
        if (loop)
        {
            iter->second->instance->Play(true);
        }
        else
        {
            iter->second->instance->Play();
        }
    }
}

void SoundEffectManager::Stop(SoundId id)
{
    auto iter = mInventory.find(id);
    if (iter != mInventory.end())
    {
        iter->second->instance->Stop();
    }
}
