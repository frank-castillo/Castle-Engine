#include "Precompiled.h"
#include "ModelComponent.h"
#include "GameWorld.h"
#include "RenderService.h"

using namespace CASTLEEngine;

void ModelComponent::Initialize()
{
    auto mm = ModelManager::Get();
    mModelId = mm->GetModelId(mFileName);

    if(mm->GetModel(mModelId) == nullptr)
    {
        mm->LoadModel(mFileName);

        for(const auto& animationFileName : mAnimationFileNames)
        {
            mm->AddAnimation(mModelId, animationFileName);
        }
    }

    auto renderService = GetOwner().GetWorld().GetService<RenderService>();
    renderService->Register(this);
}

void ModelComponent::Terminate()
{
    auto renderService = GetOwner().GetWorld().GetService<RenderService>();
    renderService->Unregister(this);
}