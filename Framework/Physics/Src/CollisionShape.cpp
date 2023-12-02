#include "Precompiled.h"
#include "CollisionShape.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Physics;

CollisionShape::~CollisionShape()
{
    ASSERT(mCollisionShape == nullptr, "CollisionShape: Terminate must be called first.");
}

void CollisionShape::Terminate()
{
    SafeDelete(mCollisionShape);
}

void CollisionShapeSphere::Initialize(float radius)
{
    ASSERT(mCollisionShape == nullptr, "CollisionShapeSphere: Collision shape has already been created");
    mCollisionShape = new btSphereShape(radius);
}

void CollisionShapeBox::Initialize(const CASTLEEngine::CEMath::Vector3& halfExtents)
{
    ASSERT(mCollisionShape == nullptr, "CollisionShapeBox: Collision shape has already been created");
    mCollisionShape = new btBoxShape(ConvertTobtVector3(halfExtents));
}

void CollisionShapeHull::Initialize(const CASTLEEngine::CEMath::Vector3& halfExtents, const CASTLEEngine::CEMath::Vector3& origin)
{
    ASSERT(mCollisionShape == nullptr, "CollisionShapeHull: Collision shape has already been created");
    btConvexHullShape* hullShape = new btConvexHullShape();

    std::vector<CASTLEEngine::CEMath::Vector3> points =
    {
        {-halfExtents.x, -halfExtents.y, -halfExtents.z},
        {-halfExtents.x, halfExtents.y, -halfExtents.z},
        {halfExtents.x, halfExtents.y, -halfExtents.z},
        {halfExtents.x, -halfExtents.y, -halfExtents.z},
        {halfExtents.x, -halfExtents.y, halfExtents.z},
        {halfExtents.x, halfExtents.y, halfExtents.z},
        {-halfExtents.x, halfExtents.y, halfExtents.z},
        {-halfExtents.x, -halfExtents.y, halfExtents.z},
    };

    for (auto& point : points)
    {
        hullShape->addPoint(ConvertTobtVector3(point - origin), false);
    }

    hullShape->recalcLocalAabb();

    mCollisionShape = hullShape;
}
