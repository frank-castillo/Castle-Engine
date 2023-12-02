#include "Precompiled.h"
#include "RigidBody.h"
#include "CollisionShape.h"
#include "PhysicsWorld.h"

#include "Graphics/Inc/Transform.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Physics;

void CollisionTest(void* dataA, void* dataB)
{

}

RigidBody::~RigidBody()
{
    ASSERT(mRigidBody == nullptr && mMotionState == nullptr, "RigidBody: terminate must be called first.");
}

void RigidBody::Initialize(Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass)
{
    mGraphicsTransform = &graphicsTransform;
    mMass = mass;

    mMotionState = new btDefaultMotionState(ConvertTobtTransform(graphicsTransform));
    mRigidBody = new btRigidBody(mMass, mMotionState, shape.GetCollisionShape());
    mRigidBody->setUserPointer(CollisionTest);

    PhysicsWorld::Get()->Register(this);
}

void RigidBody::Terminate()
{
    PhysicsWorld::Get()->Unregister(this);
    SafeDelete(mRigidBody);
    SafeDelete(mMotionState);
}

void RigidBody::SetCollisionFilter(int flags)
{
    mRigidBody->setCollisionFlags(flags);
}

void RigidBody::SetPosition(const CASTLEEngine::CEMath::Vector3& position)
{
    mGraphicsTransform->position = position;
    mRigidBody->setWorldTransform(ConvertTobtTransform(*mGraphicsTransform));
}

void RigidBody::SetVelocity(const CASTLEEngine::CEMath::Vector3& velocity)
{
    mRigidBody->activate(true);
    mRigidBody->setLinearVelocity(ConvertTobtVector3(velocity));
}

void RigidBody::ApplyForce(const CASTLEEngine::CEMath::Vector3& force)
{
    mRigidBody->activate(true);
    mRigidBody->applyCentralImpulse(ConvertTobtVector3(force));
}

bool RigidBody::IsDynamic() const
{
    return mMass > 0.0f;
}

void RigidBody::UpdateTransform()
{
    ApplybtTransformToTransform(mRigidBody->getWorldTransform(), *mGraphicsTransform);
}

void RigidBody::UpdateWorldTransform()
{
    mRigidBody->setWorldTransform(ConvertTobtTransform(*mGraphicsTransform));
}

void RigidBody::OnCollision(void* otherObj)
{

}

CASTLEEngine::CEMath::Vector3 RigidBody::GetLinearVelocity()
{
    return ConvertToVector3(mRigidBody->getLinearVelocity());
}
