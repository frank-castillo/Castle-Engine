#pragma once

#include "Component.h"
#include <Graphics/Inc/MeshTypes.h>
#include <Graphics/Inc/RenderObject.h>

namespace CASTLEEngine
{
	class MeshComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::MeshComponent);

		void Initialize() override;
		void Terminate() override;

		void CreateCube(float size);
		void CreateSphere(int slices, int rings, float radius);
		void CreatePlane(int rows, int columns, float spacing);

		void SetDiffuseMap(const char* fileName);
		void SetDisplacementMap(const char* fileName);
		void SetNormalMap(const char* fileName);
		void SetSpecularMap(const char* fileName);

		void SetMaterial(const Graphics::Material& material);

		const Graphics::RenderObject& GetRenderObject() const;

	private:
		Graphics::Mesh mMesh;
		Graphics::RenderObject mRenderObject;

		std::string mDiffuseMap;
		std::string mDisplacementMap;
		std::string mNormalMap;
		std::string mSpecularMap;
	};
}
