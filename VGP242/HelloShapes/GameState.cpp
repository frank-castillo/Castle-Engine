#include "GameState.h"
#include <Input/Inc/InputSystem.h>

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::Input;

void GameState::Initialize()
{
    // NDC - Normalized Device Coordinate
   //
   //            +-----------------+
   //           /                 /|
   //     1.0  +-----------------+ |
   //          |        ^        | |
   //          |        |        | |
   //          | <------+------> | |
   //          |        |        | | 1.0
   //          |        v        |/
   //    -1.0  +-----------------+ 0.0
   //      -1.0               1.0
   //

    OnCreateShape();

    auto device = GraphicsSystem::Get()->GetDevice();

    //============================================================================
    // Create the vertex buffer
    D3D11_BUFFER_DESC bufferDesc{};
    bufferDesc.ByteWidth = static_cast<UINT>(mVertices.size() * sizeof(Vertex));
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA initData{};
    initData.pSysMem = mVertices.data(); // What am I storing
    HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
    ASSERT(SUCCEEDED(hr), "Failed to create vertex buffer");

    //============================================================================
    // Create the vertex shader
    DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
    ID3DBlob* shaderBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    hr = D3DCompileFromFile
    (
        L"../../Assets/Shaders/DoSomething.fx",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VS", "vs_5_0",
        shaderFlags, 0, &shaderBlob, &errorBlob
    );

    if (errorBlob && errorBlob->GetBufferPointer())
    {
        LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
    }
    ASSERT(SUCCEEDED(hr), "Failed to compile vertex shader");

    hr = device->CreateVertexShader
    (
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        nullptr,
        &mVertexShader
    );
    ASSERT(SUCCEEDED(hr), "Failed to create vertex shader");

    //============================================================================
    // Create the input
    std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;
    vertexLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });
    vertexLayout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });

    hr = device->CreateInputLayout
    (
        vertexLayout.data(),
        (UINT)vertexLayout.size(),
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        &mInputLayout
    );
    ASSERT(SUCCEEDED(hr), "Failed to create input layout");

    SafeRelease(shaderBlob);
    SafeRelease(errorBlob);

    //============================================================================
    // Create the Pixer shader
    hr = D3DCompileFromFile
    (
        L"../../Assets/Shaders/DoSomething.fx",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PS", "ps_5_0",
        shaderFlags, 0, &shaderBlob, &errorBlob
    );

    if (errorBlob && errorBlob->GetBufferPointer())
    {
        LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
    }
    ASSERT(SUCCEEDED(hr), "Failed to compile pixel shader");

    hr = device->CreatePixelShader
    (
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        nullptr,
        &mPixelShader
    );
    ASSERT(SUCCEEDED(hr), "Failed to create pixel shader");

    SafeRelease(shaderBlob);
    SafeRelease(errorBlob);
}

void GameState::Terminate()
{
    SafeRelease(mVertexBuffer);
    SafeRelease(mVertexShader);
    SafeRelease(mInputLayout);
    SafeRelease(mPixelShader);
}

void GameState::Update(float deltaTime)
{
    auto inputSystem = InputSystem::Get();

    if (inputSystem->IsKeyPressed(KeyCode::NUMPAD1))
    {
        GraphicsSystem::Get()->SetClearColor(CASTLEEngine::Colors::Red);
    }
    else if (inputSystem->IsKeyPressed(KeyCode::NUMPAD2))
    {
        GraphicsSystem::Get()->SetClearColor(CASTLEEngine::Colors::Green);
    }
}

void GameState::Render()
{
    auto context = GraphicsSystem::Get()->GetContext();

    context->VSSetShader(mVertexShader, nullptr, 0);
    context->IASetInputLayout(mInputLayout); // How the shader values are determined
    context->PSSetShader(mPixelShader, nullptr, 0);

    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
    context->Draw((UINT)mVertices.size(), 0);
}

void GameState::DebugUI()
{
}

void GameState::OnCreateShape()
{
    mVertices.push_back({ CEMath::Vector3(0.0f, 0.5f, 0.0f), Colors::Blue });
    mVertices.push_back({ CEMath::Vector3(0.5f, -0.5f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(-0.5f, -0.5f, 0.0f), Colors::Yellow });

    mVertices.push_back({ CEMath::Vector3(-0.5f, -0.5f, 0.0f), Colors::MediumPurple });
    mVertices.push_back({ CEMath::Vector3(-1.0f, 0.5f, 0.0f), Colors::AliceBlue });
    mVertices.push_back({ CEMath::Vector3(0.0f, 0.5f, 0.0f), Colors::Aquamarine });

    mVertices.push_back({ CEMath::Vector3(0.0f, 0.5f, 0.0f), Colors::MintCream });
    mVertices.push_back({ CEMath::Vector3(1.0f, 0.5f, 0.0f), Colors::MistyRose });
    mVertices.push_back({ CEMath::Vector3(0.5f, -0.5f, 0.0f), Colors::MediumOrchid });
}

void Triangle::OnCreateShape()
{
    mVertices.push_back({ CEMath::Vector3(-0.1f, -0.1f, 0.0f), Colors::Blue });
    mVertices.push_back({ CEMath::Vector3(0.0f, -0.5f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(-0.2f, -0.5f, 0.0f), Colors::Yellow });
}

void TriForce::OnCreateShape()
{
    mVertices.push_back({ CEMath::Vector3(-0.1f, -0.1f, 0.0f), Colors::Blue });
    mVertices.push_back({ CEMath::Vector3(0.0f, -0.5f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(-0.2f, -0.5f, 0.0f), Colors::Yellow });

    mVertices.push_back({ CEMath::Vector3(0.0f, 0.3f, 0.0f), Colors::Aqua });
    mVertices.push_back({ CEMath::Vector3(0.1f, -0.1f, 0.0f), Colors::Azure });
    mVertices.push_back({ CEMath::Vector3(-0.1f, -0.1f, 0.0f), Colors::Yellow });

    mVertices.push_back({ CEMath::Vector3(0.1f, -0.1f, 0.0f), Colors::Beige });
    mVertices.push_back({ CEMath::Vector3(0.2f, -0.5f, 0.0f), Colors::Coral });
    mVertices.push_back({ CEMath::Vector3(0.0f, -0.5f, 0.0f), Colors::MintCream });
}

void Heart::OnCreateShape()
{
    mVertices.push_back({ CEMath::Vector3(0.0f, 0.0f, 0.0f), Colors::PaleVioletRed });
    mVertices.push_back({ CEMath::Vector3(0.0f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.1f, 0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(0.0f, 0.0f, 0.0f), Colors::PaleVioletRed });
    mVertices.push_back({ CEMath::Vector3(-0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.0f, 0.2f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(0.0f, 0.0f, 0.0f), Colors::PaleVioletRed });
    mVertices.push_back({ CEMath::Vector3(0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.1f, -0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(0.0f, 0.0f, 0.0f), Colors::PaleVioletRed });
    mVertices.push_back({ CEMath::Vector3(-0.1f, -0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(-0.1f, 0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(0.0f, 0.0f, 0.0f), Colors::PaleVioletRed });
    mVertices.push_back({ CEMath::Vector3(0.1f, -0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.0f, -0.2f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(0.0f, 0.0f, 0.0f), Colors::PaleVioletRed });
    mVertices.push_back({ CEMath::Vector3(0.0f, -0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(-0.1f, -0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(0.0f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.1f, 0.3f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.1f, 0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(0.0f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.1f, 0.3f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.1f, 0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(0.1f, 0.3f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.2f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.1f, 0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.2f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.2f, 0.0f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.2f, 0.0f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(0.1f, -0.1f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(0.0f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(-0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(-0.1f, 0.3f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(-0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(-0.2f, 0.2f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(-0.1f, 0.3f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(-0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(-0.2f, 0.0f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(-0.2f, 0.2f, 0.0f), Colors::Red });

    mVertices.push_back({ CEMath::Vector3(-0.1f, 0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(-0.1f, -0.1f, 0.0f), Colors::Red });
    mVertices.push_back({ CEMath::Vector3(-0.2f, 0.0f, 0.0f), Colors::Red });
}