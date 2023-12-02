#include "Precompiled.h"
#include "RigidBodyComponent.h"

#include "GameWorld.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"

using namespace CASTLEEngine;

void RigidBodyComponent::Initialize()
{
    TransformComponent* transform = GetOwner().GetComponent<TransformComponent>();
    ColliderComponent* collider = GetOwner().GetComponent<ColliderComponent>();
    mRigidBody.Initialize(*transform, *collider->mCollisionShape, mMass);
    mRigidBody.GetRigidBody()->setUserPointer(&GetOwner());
}

void RigidBodyComponent::Terminate()
{
    mRigidBody.Terminate();
}

void RigidBodyComponent::SetPosition(const CASTLEEngine::CEMath::Vector3& postion)
{
    mRigidBody.SetPosition(postion);
}

void RigidBodyComponent::SetMass(float mass)
{
    mMass = mass;
}

void RigidBodyComponent::ApplyForce(CASTLEEngine::CEMath::Vector3& force)
{
    mRigidBody.ApplyForce(force);
}

void RigidBodyComponent::SetVelocity(CASTLEEngine::CEMath::Vector3& velocity)
{
    mRigidBody.SetVelocity(velocity);
}

void RigidBodyComponent::UpdateRigidBodyTransform()
{
    mRigidBody.UpdateWorldTransform();
}

CASTLEEngine::CEMath::Vector3 RigidBodyComponent::GetLinearVelocity()
{
    return mRigidBody.GetLinearVelocity();
}
