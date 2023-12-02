#pragma once

#include "Common.h"
#include "App.h"
#include "AppState.h"
#include "Component.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "GameObjectHandle.h"
#include "GameWorld.h"
#include "Service.h"
#include "TypeIds.h"

// Components
#include "AnimatorComponent.h"
#include "CameraComponent.h"
#include "ColliderComponent.h"
#include "FPSCameraControllerComponent.h"
#include "MeshComponent.h"
#include "ModelComponent.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "PlayerControllerComponent.h"
#include "PlayerInputControllerComponent.h"

// Services
#include "CameraService.h"
#include "RenderService.h"

// Audio
#include "AudioSystem.h"
#include "SoundEffectManager.h"

namespace CASTLEEngine
{
    App& MainApp();
}