#include "Precompiled.h"
#include "ColliderComponent.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Physics;

void ColliderComponent::Initialize()
{
    ASSERT(mCollisionShape != nullptr, "CollisionShape: shape was not set");
}

void ColliderComponent::Terminate()
{
    mCollisionShape->Terminate();
    delete mCollisionShape;
}

void ColliderComponent::SetSphereCollider(float radius)
{
    ASSERT(mCollisionShape == nullptr, "ColliderComponent: is already set.");
    CollisionShapeSphere* sphere = new CollisionShapeSphere();
    sphere->Initialize(radius);
    mCollisionShape = sphere;
}

void ColliderComponent::SetBoxCollider(const CEMath::Vector3& halfExtents)
{
    ASSERT(mCollisionShape == nullptr, "ColliderComponent: is already set.");
    CollisionShapeBox* box = new CollisionShapeBox();
    box->Initialize(halfExtents);
    mCollisionShape = box;
}

void ColliderComponent::SetHullCollider(const CEMath::Vector3& halfExtents, const CEMath::Vector3& origin)
{
    ASSERT(mCollisionShape == nullptr, "ColliderComponent: is already set.");
    CollisionShapeHull* box = new CollisionShapeHull();
    box->Initialize(halfExtents, origin);
    mCollisionShape = box;
}
