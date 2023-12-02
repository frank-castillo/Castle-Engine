#pragma once
#include "Animator.h"
#include "Material.h"
#include "MeshBuffer.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Skeleton.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;

namespace CASTLEEngine::Graphics
{
    struct Model;
    class RenderObject
    {
    public:
        void Terminate();

        Transform transform;

        Material material;

        TextureId diffuseMapId;
        TextureId normalMapId;
        TextureId displacementMapId;
        TextureId specularMapId;

        ModelId modelId = 0;
        MeshBuffer meshBuffer;
        const Skeleton* skeleton = nullptr;
        const Animator* animator = nullptr;
    };

    using RenderGroup = std::vector<RenderObject>;
    [[nodiscard]] RenderGroup CreateRenderGroup(ModelId modelId, const Animator* animator = nullptr);
    [[nodiscard]] RenderGroup CreateRenderGroup(const Model& model, const Animator* animator = nullptr);
    void CleanUpRenderGroup(RenderGroup& renderGroup);

    template<class Effect>
    void DrawRenderGroup(Effect& effect, const RenderGroup& renderGroup)
    {
        for (auto& renderObject : renderGroup)
        {
            effect.Render(renderObject);
        }
    }
}