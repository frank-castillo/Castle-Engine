#pragma once

#include "Common.h"

namespace CASTLEEngine
{
    enum class ComponentId
    {
        TransformComponent,
        CameraComponent,
        FPSCameraControllerComponent,
        ModelComponent,
        MeshComponent,
        ColliderComponent,
        RigidBodyComponent,
        AnimatorComponent,
        ProjectileMovementComponent,
        AudioComponent,
        PlayerControllerComponent,
        PlayerInputControllerComponent,

        Count
    };

    enum class ServiceId
    {
        CameraService,
        RenderService,

        Count
    };
}

#define SET_TYPE_ID(id)\
    static uint32_t StaticGetTypeId() { return static_cast<uint32_t>(id); }\
    uint32_t GetTypeId() const override { return StaticGetTypeId(); }