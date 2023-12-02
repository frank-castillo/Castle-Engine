#pragma once
#include "Particle.h"

struct ParticleSystemInfo
{
    ParticleInfo particleInfo;
    int minParticlesPerEmit = 0.0f;
    int maxParticlesPerEmit = 0.0f;
    float minTimeBetweenParticles = 0.0f;
    float maxTimeBetweenParticles = 0.0f;
    float minSpawnAngle = 0.0f;
    float maxSpawnAngle = 0.0f;
    float minParticleSpeed = 0.0f;
    float maxParticleSpeed = 0.0f;
    float lifeTime = 0.0f;
    int maxParticles = 100;
};

class ParticleSystem
{
public:
    ParticleSystem();
    ~ParticleSystem();

    void Initialize(const ParticleSystemInfo& info, const CASTLEEngine::CEMath::Vector3& spawnPosition, const CASTLEEngine::CEMath::Vector3& spawnDirection, float delay = 0.0f);
    void Terminate();
    void Update(float deltaTime);
    void Render();

private:
    void SpawnParticles();
    void SpawnParticle();

    using Particles = std::vector<Particle>;
    Particles mParticles;
    int mNextAvailableParticleIndex;
    float mLifeTime;
    float mNextSpawn;
    
    ParticleSystemInfo mInfo;
    CASTLEEngine::CEMath::Vector3 mSpawnPosition;
    CASTLEEngine::CEMath::Vector3 mSpawnDirection;
};