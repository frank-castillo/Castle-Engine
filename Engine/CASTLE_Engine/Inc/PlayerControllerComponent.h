#pragma once

#include "Component.h"

namespace CASTLEEngine
{
    class RigidBodyComponent;
    class TransformComponent;

    class PlayerControllerComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::PlayerControllerComponent);

        void Initialize() override;
        void Update(float deltaTime) override;
        void DebugUI() override;

        void Move(Vector3 inputDirection, float deltaTime);
        void Jump();
        void Rotate(Vector3 lookAt);
        void Reset();

    private:
        RigidBodyComponent* mRigidBodyComponent;
        TransformComponent* mTransformComponent;

        float mMoveSpeed;
        float mJumpForce;
        float mCurrentJump;
        unsigned int mMaxJumps;

        bool mCanJump;
        bool mIsGrounded;
    };
}