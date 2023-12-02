#pragma once
#include <CASTLE_Engine/Inc/CASTLE_Engine.h>

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;

class GameState : public CASTLEEngine::AppState
{
public:
    virtual ~GameState() = default;

    virtual void Initialize() override;
    virtual void Terminate() override;

    virtual void Update(float deltaTime) override;
    virtual void Render() override;
};