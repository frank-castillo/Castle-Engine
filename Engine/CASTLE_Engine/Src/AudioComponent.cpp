#include "Precompiled.h"
#include "AudioComponent.h"
#include "GameWorld.h"

void AudioComponent::Update(float deltaTime)
{
    if (Input::InputSystem::Get()->IsKeyPressed(Input::KeyCode::SPACE))
    {
        SoundEffectManager::Get()->Stop(mSoundEffectId);
        SoundEffectManager::Get()->Play(mSoundEffectId, false);
    }
}

void AudioComponent::DebugUI()
{
    
}

void AudioComponent::EditorUI()
{
    
}

void AudioComponent::LoadSoundEffect(const std::filesystem::path& fileName)
{
    mSoundEffectId = SoundEffectManager::Get()->Load(fileName);
}

void AudioComponent::SetAsOneShot(bool canLoop)
{
    mCanLoop = canLoop;
}

void AudioComponent::PlaySoundEffect()
{
    SoundEffectManager::Get()->Play(mSoundEffectId, mCanLoop);
}

void AudioComponent::StopSoundEffect()
{
    SoundEffectManager::Get()->Stop(mSoundEffectId);
}
