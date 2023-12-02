#pragma once

#include "Component.h"

namespace CASTLEEngine
{
    class ColliderComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::ColliderComponent);

        void Initialize() override;
        void Terminate() override;

        void SetSphereCollider(float radius);
        void SetBoxCollider(const CEMath::Vector3& halfExtents);
        void SetHullCollider(const CEMath::Vector3& halfExtents, const CEMath::Vector3& origin);

    private:
        friend class RigidBodyComponent;
        Physics::CollisionShape* mCollisionShape = nullptr;
    };
}