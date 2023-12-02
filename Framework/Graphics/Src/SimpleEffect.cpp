#include "Precompiled.h"
#include "SimpleEffect.h"

#include "Camera.h"
#include "MeshBuffer.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;

void SimpleEffect::Initialize()
{
    std::filesystem::path filePath = L"../../Assets/Shaders/DoTransform.fx";
    mVertexShader.Initialize<VertexPC>(filePath);
    mPixelShader.Initialize(filePath);
    mConstantBuffer.Initialize(sizeof(CEMath::Matrix4));
    mBlendState.Initialize(BlendState::Mode::AlphaBlend);
}

void SimpleEffect::Terminate()
{
    mBlendState.Terminate();
    mConstantBuffer.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
}

void SimpleEffect::Begin()
{
    mVertexShader.Bind();
    mPixelShader.Bind();
    mConstantBuffer.BindVS(0);
    mBlendState.Set();
}

void SimpleEffect::End()
{
    mBlendState.ClearState();
}

void SimpleEffect::Render(const RenderObject& renderObject)
{
    CEMath::Matrix4 matWorld = renderObject.transform.GetMatrix4();
    CEMath::Matrix4 matView = mCamera->GetViewMatrix();
    CEMath::Matrix4 matProj = mCamera->GetProjectionMatrix();
    CEMath::Matrix4 matFinal = matWorld * matView * matProj;
    CEMath::Matrix4 wvp = Transpose(matFinal);

    mConstantBuffer.Update(&wvp);
    
    renderObject.meshBuffer.Render();
}

void SimpleEffect::SetCamera(const Camera& camera)
{
    mCamera = &camera;
}
