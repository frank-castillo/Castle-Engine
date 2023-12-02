#pragma once

#include "Component.h"

namespace CASTLEEngine
{
    class ProjectileMovementComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::ProjectileMovementComponent);

        void Initialize() override;
        void Update(float deltaTime) override;
        void DebugUI() override;
        void EditorUI() override;

        void SetMoveSpeed(float speed) { mMoveSpeed = speed; }
        void SetTimeToDie(float time) { mTimeToDie = time; }

        float GetMoveSpeed() const { return mMoveSpeed; }

    private:
        float mTimeToDie = 20.0f;
        float mMoveSpeed = 1.0f;
    };
}