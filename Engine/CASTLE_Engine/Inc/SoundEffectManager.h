#pragma once

namespace DirectX
{
    class SoundEffect;
    class SoundEffectInstance;
}

namespace CASTLEEngine
{
    using SoundId = std::size_t;

    class SoundEffectManager final
    {
    public:
        static void StaticInitialize(const std::filesystem::path& root);
        static void StaticTerminate();
        static SoundEffectManager* Get();

    public:
        SoundEffectManager();
        ~SoundEffectManager();

        SoundEffectManager(const SoundEffectManager&) = delete;
        SoundEffectManager& operator=(const SoundEffectManager&) = delete;

        void SetRootPath(const std::filesystem::path& path);

        SoundId Load(const std::filesystem::path& fileName);
        void Clear();

        void Play(SoundId id, bool loop = false);
        void Stop(SoundId id);

    private:
        struct Entry
        {
            std::unique_ptr<DirectX::SoundEffect> effect;
            std::unique_ptr<DirectX::SoundEffectInstance> instance;
        };

        std::filesystem::path mRoot;
        std::unordered_map<SoundId, std::unique_ptr<Entry>> mInventory;
    };
}