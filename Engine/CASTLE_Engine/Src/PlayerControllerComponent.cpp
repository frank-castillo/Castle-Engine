#include "Precompiled.h"

#include "PlayerControllerComponent.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::CEMath;

void CASTLEEngine::PlayerControllerComponent::Initialize()
{
    mRigidBodyComponent = GetOwner().GetComponent<RigidBodyComponent>();
    mTransformComponent = GetOwner().GetComponent<TransformComponent>();

    ASSERT(mRigidBodyComponent != nullptr && mTransformComponent != nullptr, "PlayerControllerComponent: Failed to initialize, no Rigidbody or Transform component found.");

    mIsGrounded = true;
    mMoveSpeed = 5.0f;
    mMaxJumps = 2;
    mJumpForce = 5.0f;
}

void CASTLEEngine::PlayerControllerComponent::Update(float deltaTime)
{
    Vector3 velocity = mRigidBodyComponent->GetLinearVelocity();

    if (velocity.y <= 0.0f)
    {
        mIsGrounded = true;
    }
    else
    {
        mIsGrounded = false;
    }
}

void CASTLEEngine::PlayerControllerComponent::Move(Vector3 inputDirection, float deltaTime)
{
    Vector3 moveForce = inputDirection * mMoveSpeed * deltaTime * 25.0f;
    mRigidBodyComponent->SetVelocity(moveForce);
    Vector3 dir = (mTransformComponent->position + moveForce) - mTransformComponent->position;
    dir = Normalize(dir);
    Rotate(dir);
}

void PlayerControllerComponent::Reset()
{
    if (CEMath::Magnitude(mRigidBodyComponent->GetLinearVelocity()) <= 0.1f)
    {
        Rotate(Vector3::ZAxis);
    }
}

void PlayerControllerComponent::Rotate(Vector3 lookAt)
{
    mTransformComponent->rotation = Quaternion::LookRotation(lookAt, Vector3::YAxis);
    mRigidBodyComponent->UpdateRigidBodyTransform();
}

void PlayerControllerComponent::Jump()
{
    if (mIsGrounded)
    {
        mCurrentJump = 0;
        mCanJump = true;
    }

    if (mCanJump)
    {
        Vector3 up = Vector3::YAxis * mJumpForce;
        mRigidBodyComponent->SetVelocity(up);

        // Add limit
        ++mCurrentJump;

        if (mCurrentJump >= mMaxJumps)
        {
            mCanJump = false;
            mIsGrounded = false;
        }
    }
}

void PlayerControllerComponent::DebugUI()
{

}
