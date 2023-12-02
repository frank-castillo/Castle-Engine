#include "Precompiled.h"
#include "ModelManager.h"
#include "ModelIO.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;

namespace
{
    std::unique_ptr<ModelManager> sModelManager;
}

void ModelManager::StaticInitialize()
{
    ASSERT(sModelManager == nullptr, "ModelManager -- System already initiliazed");
    sModelManager = std::make_unique<ModelManager>();
}

void ModelManager::StaticTerminate()
{
    sModelManager.reset();
}

ModelManager* ModelManager::Get()
{
    ASSERT(sModelManager != nullptr, "ModelManager -- System not initiliazed");
    return sModelManager.get();
}

ModelId ModelManager::GetModelId(const std::filesystem::path& filepath)
{
    return std::filesystem::hash_value(filepath);
}

ModelId ModelManager::LoadModel(const std::filesystem::path& filepath)
{
    const auto modelId = GetModelId(filepath);
    auto [iter, success] = mInventory.insert({ modelId, nullptr });

    if (success)
    {
        auto& modelPtr = iter->second;
        modelPtr = std::make_unique<Model>();
        ModelIO::LoadModel(filepath, *modelPtr);
        ModelIO::LoadMaterial(filepath, *modelPtr);
        ModelIO::LoadSkeleton(filepath, *modelPtr);
        ModelIO::LoadAnimations(filepath, *modelPtr);
    }

    return modelId;
}

void ModelManager::AddAnimation(ModelId id, const std::filesystem::path& filepath)
{
    auto model = mInventory.find(id);
    ASSERT(model != mInventory.end(), "ModelManager: need to load the model first");
    ModelIO::LoadAnimations(filepath, *model->second);
}

const Model* ModelManager::GetModel(ModelId id)
{
    auto model = mInventory.find(id);

    if (model != mInventory.end())
    {
        return model->second.get();
    }

    return nullptr;
}