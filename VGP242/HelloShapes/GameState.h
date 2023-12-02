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
    virtual void DebugUI() override;

protected:
    struct Vertex
    {
        CASTLEEngine::CEMath::Vector3 position;
        CASTLEEngine::Color color;
    };

    virtual void OnCreateShape();

    std::vector<Vertex> mVertices;

    ID3D11Buffer* mVertexBuffer = nullptr;
    ID3D11VertexShader* mVertexShader = nullptr;
    ID3D11InputLayout* mInputLayout = nullptr;
    ID3D11PixelShader* mPixelShader = nullptr;
};

class Triangle : public GameState
{
public:
    virtual ~Triangle() = default;

protected:
    void OnCreateShape() override;
};

class TriForce : public GameState
{
public:
    virtual ~TriForce() = default;

protected:
    void OnCreateShape() override;
};

class Heart : public GameState
{
public:
    virtual ~Heart() = default;

protected:
    void OnCreateShape() override;
};