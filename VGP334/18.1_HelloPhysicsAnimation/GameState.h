#pragma once
#include <CASTLE_Engine/Inc/CASTLE_Engine.h>
#include "ParticleSystem.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::Physics;

class GameState : public CASTLEEngine::AppState
{
public:
    virtual ~GameState() = default;

    virtual void Initialize() override;
    virtual void Terminate() override;
    
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void DebugUI() override;
protected:
    Camera mCamera;
    DirectionalLight mDirectionalLight;

    RenderObject mBall;
    RigidBody mBallRigidBody;
    CollisionShapeSphere mSphereCollisionShape;

    RenderObject mGround;
    RigidBody mGroundRigidBody;
    CollisionShapeBox mGroundCollisionShape;

    ParticleSystem mParticleSystem;

    StandardEffect mStandardEffect;
    SimpleEffect mParticleEffect;
};