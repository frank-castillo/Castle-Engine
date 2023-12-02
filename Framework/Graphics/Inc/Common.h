#pragma once

// Engine Headers
#include <Core/Inc/Core.h>
#include <Math/Inc/CEMath.h>

// DirectX Headers
#include <d3d11_1.h>
#include <d3dcompiler.h>

// Externals
#include <ImGui/Inc/imgui.h>

// DirectX Libraries
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

template <class T>
inline void SafeRelease(T*& ptr)
{
    if (ptr)
    {
        ptr->Release();
        ptr = nullptr;
    }
}