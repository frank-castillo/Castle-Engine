#pragma once

#include "Component.h"
#include "SoundEffectManager.h"

namespace CASTLEEngine
{

    class AudioComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::AudioComponent);

        void Update(float deltaTime) override;
        void DebugUI() override;
        void EditorUI() override;

        void LoadSoundEffect(const std::filesystem::path& fileName);
        void SetAsOneShot(bool canLoop = false);
        void PlaySoundEffect();
        void StopSoundEffect();

    private:
        SoundId mSoundEffectId;
        bool mCanLoop;
    };
}
