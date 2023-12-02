#pragma once

#include <CASTLE_Engine/Inc/CASTLE_Engine.h>

struct ParticleInfo
{
    float lifetime = 0.0f;
    CASTLEEngine::Color startColor = CASTLEEngine::Colors::White;
    CASTLEEngine::Color endColor = CASTLEEngine::Colors::White;
    CASTLEEngine::CEMath::Vector3 startScale = CASTLEEngine::CEMath::Vector3::One;
    CASTLEEngine::CEMath::Vector3 endScale = CASTLEEngine::CEMath::Vector3::One;
};

class Particle
{
public:
    Particle() = default;

    void Initialize(const ParticleInfo& info);
    void Terminate();

    void Activate(const CASTLEEngine::CEMath::Vector3& pos, const CASTLEEngine::CEMath::Vector3& dir, float speed);
    void Update(float deltaTime);
    void Render(CASTLEEngine::Graphics::SimpleEffect& effect);

private:
    CASTLEEngine::Graphics::MeshPC mMesh;
    CASTLEEngine::Graphics::RenderObject mParticle;
    CASTLEEngine::Physics::RigidBody mRigidBody;
    CASTLEEngine::Physics::CollisionShapeSphere mSphere;

    bool mIsActive = false;
    ParticleInfo mInfo;
    float mLifeTime = 0.0f;
    float mLifeTimeDuration = 0.0f;
    CASTLEEngine::Color mCurrentColor = CASTLEEngine::Colors::White;
    CASTLEEngine::CEMath::Vector3 mCurrentScale = CASTLEEngine::CEMath::Vector3::One;
};
