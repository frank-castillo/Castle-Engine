#pragma once

#include <CASTLE_Engine/Inc/CASTLE_Engine.h>
#include "ParticleSystem.h"

class CASTLEEngine::GameWorld;

class GameState : public CASTLEEngine::AppState
{
public:
    virtual ~GameState() = default;

    virtual void Initialize() override;
    virtual void Terminate() override;

    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void DebugUI() override;
    virtual void EditorUI() override;

protected:
    GameWorld mGameWorld;
};