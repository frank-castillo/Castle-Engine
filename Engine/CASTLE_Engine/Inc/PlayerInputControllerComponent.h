#pragma once

#include "Component.h"

namespace CASTLEEngine
{
    class PlayerControllerComponent;

    class PlayerInputControllerComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::PlayerInputControllerComponent);

        void Initialize() override;
        void Terminate() override;
        void Update(float deltaTime) override;
        void DebugUI() override;

    private:
        PlayerControllerComponent* mPlayerController;
        CASTLEEngine::CEMath::Vector3 mDirection;
    };
}