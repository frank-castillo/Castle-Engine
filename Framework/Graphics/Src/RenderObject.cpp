#include "Precompiled.h"
#include "RenderObject.h"
#include "Model.h"

void RenderObject::Terminate()
{
    diffuseMapId = 0;
    specularMapId = 0;
    displacementMapId = 0;
    normalMapId = 0;
    modelId = 0;
    animator = nullptr;
    meshBuffer.Terminate();
}

RenderGroup Graphics::CreateRenderGroup(ModelId modelId, const Animator* animator)
{
    auto model = ModelManager::Get()->GetModel(modelId);
    RenderGroup renderGroup = CreateRenderGroup(*model, animator);

    for (auto& renderObject : renderGroup)
    {
        renderObject.modelId = modelId;
    }

    return renderGroup;
}

RenderGroup Graphics::CreateRenderGroup(const Model& model, const Animator* animator)
{
    RenderGroup renderGroup;
    renderGroup.reserve(model.meshData.size());

    auto TryLoadTexture = [](const auto& textureName) -> TextureId
    {
        if (textureName.empty())
        {
            return 0;
        }

        return TextureManager::Get()->LoadTexture(textureName, false);
    };

    for (auto& meshData : model.meshData)
    {
        auto& renderObject = renderGroup.emplace_back();
        auto& materialData = model.materialData[meshData.materialIndex];
        renderObject.material = materialData.material;
        renderObject.diffuseMapId = TryLoadTexture(materialData.diffuseMapName);
        renderObject.specularMapId = TryLoadTexture(materialData.specularMapName);
        renderObject.displacementMapId = TryLoadTexture(materialData.displacementMapName);
        renderObject.normalMapId = TryLoadTexture(materialData.normalMapName);

        renderObject.skeleton = model.skeleton.get();
        renderObject.animator = animator;

        renderObject.meshBuffer.Initialize(meshData.mesh);
    }

    return renderGroup;
}

void Graphics::CleanUpRenderGroup(RenderGroup& renderGroup)
{
    for (auto& renderObject : renderGroup)
    {
        renderObject.Terminate();
    }
}