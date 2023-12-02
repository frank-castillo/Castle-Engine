#pragma once
#include "Component.h"

namespace CASTLEEngine
{
    class RigidBodyComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::RigidBodyComponent);

        void Initialize() override;
        void Terminate() override;

        void SetPosition(const CASTLEEngine::CEMath::Vector3& postion);
        void SetMass(float mass);
        void ApplyForce(CASTLEEngine::CEMath::Vector3& force);
        void SetVelocity(CASTLEEngine::CEMath::Vector3& velocity);
        void UpdateRigidBodyTransform();
        CASTLEEngine::CEMath::Vector3 GetLinearVelocity();

    private:
        Physics::RigidBody mRigidBody;
        float mMass = 0.0f;
    };
}