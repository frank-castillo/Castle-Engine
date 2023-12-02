#include "Particle.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;

void Particle::Initialize(const ParticleInfo& info)
{
    mIsActive = false;
    mInfo = info;
    mLifeTime = 0.0f;
    mLifeTimeDuration = 0.0f;

    mMesh = MeshBuilder::CreateSpherePC(10.0f, 10.0f, 0.1f);
    mParticle.meshBuffer.Initialize(nullptr, sizeof(VertexPC), mMesh.vertices.size(), mMesh.indices.data(), mMesh.indices.size());

    mSphere.Initialize(0.1f);
    mRigidBody.Initialize(mParticle.transform, mSphere, 0.1f);
    mRigidBody.SetCollisionFilter(0);
}

void Particle::Terminate()
{
    mRigidBody.Terminate();
    mSphere.Terminate();
    mParticle.Terminate();
}

void Particle::Activate(const CASTLEEngine::CEMath::Vector3& pos, const CASTLEEngine::CEMath::Vector3& dir, float speed)
{
    mLifeTime = 0.0f;
    mLifeTimeDuration = mInfo.lifeTime;
    mIsActive = true;
    mRigidBody.SetPosition(pos);
    mRigidBody.SetVelocity(dir * speed);
    mRigidBody.SetCollisionFilter(0);
}

void Particle::Update(float deltaTime)
{
    if (mIsActive)
    {
        mLifeTime += deltaTime;
        float t = CEMath::Clamp(mLifeTime / mLifeTimeDuration, 0.0f, 1.0f);
        mCurrentColor = CEMath::Lerp(mInfo.startColor, mInfo.endColor, t);
        mCurrentScale = CEMath::Lerp(mInfo.startScale, mInfo.endScale, t);
        mIsActive = mLifeTime < mLifeTimeDuration;
    }
    else
    {
        mRigidBody.SetVelocity(Vector3::Zero);
    }
}

void Particle::Render()
{
    if (mIsActive)
    {
        for (auto& v : mMesh.vertices)
        {
            v.color = mCurrentColor;
        }

        mParticle.transform.scale = mCurrentScale;
        mParticle.meshBuffer.Update(mMesh.vertices.data(), mMesh.vertices.size());
        mParticle.meshBuffer.Render();
    }
}