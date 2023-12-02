#pragma once

namespace CASTLEEngine::Graphics
{
    struct Transform;
}

namespace CASTLEEngine::Physics
{
    class CollisionShape;

    using CollisionCallback = std::function<void(void*, void*)>;

    class RigidBody final
    {
    public:
        RigidBody() = default;
        ~RigidBody();

        void Initialize(Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass = 0.0f);
        void Terminate();

        void SetCollisionFilter(int flags);
        void SetPosition(const CASTLEEngine::CEMath::Vector3& position);
        void SetVelocity(const CASTLEEngine::CEMath::Vector3& velocity);
        void ApplyForce(const CASTLEEngine::CEMath::Vector3& force);

        CASTLEEngine::CEMath::Vector3 GetLinearVelocity();

        bool IsDynamic() const;
        void UpdateTransform();
        void UpdateWorldTransform();

        void OnCollision(void* otherObj);
        btRigidBody* GetRigidBody() { return mRigidBody; }

    private:
        friend class PhysicsWorld;

        btRigidBody* mRigidBody = nullptr;
        btDefaultMotionState* mMotionState = nullptr;
        float mMass = 0.0f;
        bool mIsDynamic;
        Graphics::Transform* mGraphicsTransform = nullptr;
    };
}