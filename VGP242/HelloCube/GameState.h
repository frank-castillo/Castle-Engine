#include <CASTLE_Engine/Inc/CASTLE_Engine.h>

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

    CASTLEEngine::Graphics::Camera mCamera;
    CASTLEEngine::Graphics::ConstantBuffer mConstantBuffer;
    CASTLEEngine::Graphics::MeshBuffer mMeshBuffer;
    CASTLEEngine::Graphics::VertexShader mVertexShader;
    CASTLEEngine::Graphics::PixelShader mPixelShader;

private:
    float mRunningTime = 0.0f;
};

class Triangle : public GameState
{
public:
    virtual ~Triangle() = default;

protected:
    void OnCreateShape() override;
};

class Cube : public GameState
{
public:
    virtual ~Cube() = default;

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