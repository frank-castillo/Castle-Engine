#pragma once

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
    virtual void CreateMesh();

    struct Vertex
    {
        CASTLEEngine::CEMath::Vector3 position;
        CASTLEEngine::Color color;
    };

    std::vector<Vertex> mVertices;

    CASTLEEngine::Graphics::Camera mCamera;
    CASTLEEngine::Graphics::ConstantBuffer mConstantBuffer;

    CASTLEEngine::Graphics::MeshPC mMesh;
    CASTLEEngine::Graphics::MeshBuffer mMeshBuffer;
    CASTLEEngine::Graphics::VertexShader mVertexShader;
    CASTLEEngine::Graphics::PixelShader mPixelShader;

private:
    float mRunningTime = 0.0f;
};