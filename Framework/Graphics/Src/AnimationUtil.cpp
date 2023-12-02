#include "Precompiled.h"

#include "AnimationUtil.h"
#include "Colors.h"
#include "SimpleDraw.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::Graphics::AnimationUtil;

namespace
{
    void ComputeBoneTransformRecursive(const Bone* bone, BoneTransforms& boneTransforms, const Animator* animator)
    {
        if (bone != nullptr)
        {
            if (animator != nullptr)
            {
                boneTransforms[bone->index] = animator->GetToParentTransform(bone);
            }
            else
            {
                boneTransforms[bone->index] = bone->toParentTransform;
            }

            if (bone->parent != nullptr)
            {
                boneTransforms[bone->index] = boneTransforms[bone->index] * boneTransforms[bone->parentIndex];
            }
            else
            {
                boneTransforms[bone->index] = bone->toParentTransform;
            }

            for (auto child : bone->children)
            {
                ComputeBoneTransformRecursive(child, boneTransforms, animator);
            }
        }
    }
}

void AnimationUtil::ComputeBoneTransform(ModelId modelId, BoneTransforms& boneTransforms, const Animator* animator)
{
    auto model = ModelManager::Get()->GetModel(modelId);

    if (model->skeleton != nullptr)
    {
        boneTransforms.resize(model->skeleton->bones.size(), CEMath::Matrix4::Identity);
        ComputeBoneTransformRecursive(model->skeleton->root, boneTransforms, animator);
    }
}

void AnimationUtil::ApplyBoneOffsets(ModelId modelId, BoneTransforms& boneTransforms)
{
    auto model = ModelManager::Get()->GetModel(modelId);

    if (model->skeleton != nullptr)
    {
        for (auto& bone : model->skeleton->bones)
        {
            boneTransforms[bone->index] = bone->offsetTransform * boneTransforms[bone->index];
        }
    }
}

void AnimationUtil::DrawSkeleton(ModelId modelId, BoneTransforms& boneTransforms)
{
    auto model = ModelManager::Get()->GetModel(modelId);

    if (model->skeleton != nullptr)
    {
        for (auto& bone : model->skeleton->bones)
        {
            if (bone->parent != nullptr)
            {
                const auto posA = CEMath::GetTranslation(boneTransforms[bone->index]);
                const auto posB = CEMath::GetTranslation(boneTransforms[bone->parentIndex]);

                SimpleDraw::AddLine(posA, posB, Colors::Aquamarine);
            }

        }
    }
}