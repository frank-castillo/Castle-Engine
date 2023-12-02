#pragma once

namespace DirectX
{
    class AudioEngine;
}

namespace CASTLEEngine
{
    class AudioSystem final
    {
    public:
        static void StaticInitialize();
        static void StaticTerminate();
        static AudioSystem* Get();

    public:
        AudioSystem();
        ~AudioSystem();

        AudioSystem(const AudioSystem&) = delete;
        AudioSystem& operator=(const AudioSystem&) = delete;

        void Initialize();
        void Terminate();

        void Update();

    private:
        friend class SoundEffectManager;

        DirectX::AudioEngine* mAudioEngine;
    };
}