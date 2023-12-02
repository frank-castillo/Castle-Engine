#include "Precompiled.h"
#include "MeshComponent.h"

#include "GameWorld.h"
#include "RenderService.h"
#include "Graphics/Inc/TextureManager.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;

void MeshComponent::Initialize()
{
	mRenderObject.meshBuffer.Initialize(mMesh);
	auto renderService = GetOwner().GetWorld().GetService<RenderService>();
	renderService->Register(this);
}

void MeshComponent::Terminate()
{
	auto renderService = GetOwner().GetWorld().GetService<RenderService>();
	renderService->Unregister(this);
	mRenderObject.Terminate();
}

void MeshComponent::CreateCube(float size)
{	 
	mMesh = MeshBuilder::CreateCube(size);
}	 
	 
void MeshComponent::CreateSphere(int slices, int rings, float radius)
{	 
	mMesh = MeshBuilder::CreateSphere(slices, rings, radius);
}	 
	 
void MeshComponent::CreatePlane(int rows, int columns, float spacing)
{
	mMesh = MeshBuilder::CreatePlane(rows, columns, spacing);
}

void MeshComponent::SetDiffuseMap(const char* fileName)
{
	mRenderObject.diffuseMapId = TextureManager::Get()->LoadTexture(fileName);
}

void MeshComponent::SetDisplacementMap(const char* fileName)
{
	mRenderObject.displacementMapId = TextureManager::Get()->LoadTexture(fileName);
}

void MeshComponent::SetNormalMap(const char* fileName)
{
	mRenderObject.normalMapId = TextureManager::Get()->LoadTexture(fileName);
}

void MeshComponent::SetSpecularMap(const char* fileName)
{
	mRenderObject.specularMapId = TextureManager::Get()->LoadTexture(fileName);
}

void MeshComponent::SetMaterial(const Graphics::Material& material)
{
	mRenderObject.material = material;
}

const RenderObject& MeshComponent::GetRenderObject() const
{
	return mRenderObject;
}
