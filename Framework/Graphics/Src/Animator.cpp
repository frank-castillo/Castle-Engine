#include "Precompiled.h"
#include "Animator.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::CEMath;
using namespace CASTLEEngine::Graphics;

BlendNode::BlendNode(BlendNode&& rhs) noexcept
    :mModelId(rhs.mModelId),
    mClipIndex(rhs.mClipIndex),
    mAnimationTick(rhs.mAnimationTick),
    mLooping(rhs.mLooping)
{
    rhs.mModelId = 0;
    rhs.mClipIndex = -1;
    rhs.mAnimationTick = 0.0f;
    rhs.mLooping = false;
}

BlendNode& BlendNode::operator=(BlendNode&& rhs) noexcept
{
    mModelId = rhs.mModelId;
    mClipIndex = rhs.mClipIndex;
    mAnimationTick = rhs.mAnimationTick;
    mLooping = rhs.mLooping;
    rhs.mModelId = 0;
    rhs.mClipIndex = -1;
    rhs.mAnimationTick = 0.0f;
    rhs.mLooping = false;
    return *this;
}

void BlendNode::PlayAnimation(ModelId id, int clipIndex, bool looping)
{
    mModelId = id;
    mClipIndex = clipIndex;
    mLooping = looping;
    mAnimationTick = 0.0f;
}

void BlendNode::Update(float deltaTime)
{
    auto model = ModelManager::Get()->GetModel(mModelId);
    const auto& animClip = model->animationClips[mClipIndex];
    mAnimationTick += animClip.ticksPerSecond * deltaTime;

    if (mAnimationTick > animClip.tickDuration)
    {
        if (mLooping)
        {
            while (mAnimationTick >= animClip.tickDuration)
            {
                mAnimationTick -= animClip.tickDuration;
            }
        }
        else
        {
            mAnimationTick = animClip.tickDuration;
        }
    }
}

bool BlendNode::GetToParentTransform(const Bone* bone, Transform& transform) const
{
    auto model = ModelManager::Get()->GetModel(mModelId);
    const auto& animClip = model->animationClips[mClipIndex];
    auto& animation = animClip.boneAnimations[bone->index];

    if (animation == nullptr)
    {
        return false;
    }

    transform = animation->GetTransform(mAnimationTick);
    return true;
}

bool BlendNode::IsFinished() const
{
    if (mLooping || mClipIndex < 0)
    {
        return false;
    }

    auto model = ModelManager::Get()->GetModel(mModelId);
    const auto& animClip = model->animationClips[mClipIndex];
    return mAnimationTick >= animClip.tickDuration;
}

void Animator::Initialize(ModelId id)
{
    mModelId = id;
}

void Animator::PlayAnimation(int clipIndex, bool looping, float blendDuration)
{
    if (mCurrentAnimation.GetClipIndex() == -1 || blendDuration <= 0.0f)
    {
        mCurrentAnimation.PlayAnimation(mModelId, clipIndex, looping);
    }
    else
    {
        mNextAnimation.PlayAnimation(mModelId, clipIndex, looping);
        mBlendDuration = blendDuration;
        mBlendTime = 0.0f;
    }
}

void Animator::Update(float deltaTime)
{
    if (mCurrentAnimation.GetClipIndex() != -1)
    {
        mCurrentAnimation.Update(deltaTime);
    }

    if (mNextAnimation.GetClipIndex() != -1)
    {
        mNextAnimation.Update(deltaTime);
    }

    if (mBlendDuration > 0.0f && mBlendTime < mBlendDuration)
    {
        mBlendTime += deltaTime;

        if (mBlendTime >= mBlendDuration)
        {
            mBlendTime = 0.0f;
            mBlendDuration = 0.0f;
            mCurrentAnimation = std::move(mNextAnimation);
        }
    }
}

bool Animator::IsFinished()
{
    return mCurrentAnimation.IsFinished();
}

size_t Animator::GetAnimationCount() const
{
    auto model = ModelManager::Get()->GetModel(mModelId);
    return model->animationClips.size();
}

Matrix4 Animator::GetToParentTransform(const Bone* bone) const
{
    Transform fromTransform;

    if (!mCurrentAnimation.GetToParentTransform(bone, fromTransform))
    {
        return bone->toParentTransform;
    }

    if (mNextAnimation.GetClipIndex() != -1)
    {
        float t = CEMath::Clamp(mBlendTime / mBlendDuration, 0.0f, 1.0f);
        Transform toTransform;

        if (!mNextAnimation.GetToParentTransform(bone, toTransform))
        {
            return bone->toParentTransform;
        }

        Transform blendedTransform;
        blendedTransform.position = CEMath::Lerp(fromTransform.position, toTransform.position, t);
        blendedTransform.rotation = CEMath::Quaternion::Slerp(fromTransform.rotation, toTransform.rotation, t);
        blendedTransform.scale = CEMath::Lerp(fromTransform.scale, toTransform.scale, t);

        return blendedTransform.GetMatrix4();
    }

    return fromTransform.GetMatrix4();
}

void BlendedAnimator::PlayAnimation(int clipIndex, bool looping, float blendDuration)
{
    // do not use
}

void BlendedAnimator::Update(float deltaTime)
{
    for (uint32_t i = 0; i < 5; ++i)
    {
        if (mBlendNodes[i].GetClipIndex() != -1)
        {
            mBlendNodes[i].Update(deltaTime);
        }
    }
}

CEMath::Matrix4 BlendedAnimator::GetToParentTransform(const Bone* bone) const
{
    Transform finalTransform;
    if (mBlendNodes[(int)BlendDirection::Center].GetToParentTransform(bone, finalTransform))
    {
        if (mWeightY > 0.1f)
        {
            Transform northTransform;
            if (mBlendNodes[(int)BlendDirection::North].GetToParentTransform(bone, northTransform))
            {
                float t = (mWeightY - 0.1f) / 0.9f;
                finalTransform.position = CEMath::Lerp(finalTransform.position, northTransform.position, t);
                finalTransform.rotation = CEMath::Quaternion::Slerp(finalTransform.rotation, northTransform.rotation, t);
                finalTransform.scale = CEMath::Lerp(finalTransform.scale, northTransform.scale, t);
            }
        }
        else if (mWeightY < -0.1f)
        {
            Transform southTransform;
            if (mBlendNodes[(int)BlendDirection::South].GetToParentTransform(bone, southTransform))
            {
                float t = (-mWeightY - 0.1f) / 0.9f;
                finalTransform.position = CEMath::Lerp(finalTransform.position, southTransform.position, t);
                finalTransform.rotation = CEMath::Quaternion::Slerp(finalTransform.rotation, southTransform.rotation, t);
                finalTransform.scale = CEMath::Lerp(finalTransform.scale, southTransform.scale, t);
            }
        }
        if (mWeightX > 0.1f)
        {
            Transform eastTransform;
            if (mBlendNodes[(int)BlendDirection::East].GetToParentTransform(bone, eastTransform))
            {
                float t = (mWeightX - 0.1f) / 0.9f;
                finalTransform.position = CEMath::Lerp(finalTransform.position, eastTransform.position, t);
                finalTransform.rotation = CEMath::Quaternion::Slerp(finalTransform.rotation, eastTransform.rotation, t);
                finalTransform.scale = CEMath::Lerp(finalTransform.scale, eastTransform.scale, t);
            }
        }
        else if (mWeightX < -0.1f)
        {
            Transform westTransform;
            if (mBlendNodes[(int)BlendDirection::West].GetToParentTransform(bone, westTransform))
            {
                float t = (-mWeightX - 0.1f) / 0.9f;
                finalTransform.position = CEMath::Lerp(finalTransform.position, westTransform.position, t);
                finalTransform.rotation = CEMath::Quaternion::Slerp(finalTransform.rotation, westTransform.rotation, t);
                finalTransform.scale = CEMath::Lerp(finalTransform.scale, westTransform.scale, t);
            }
        }
    }
    else
    {
        return bone->toParentTransform;
    }

    return finalTransform.GetMatrix4();
}

void BlendedAnimator::SetAnimation(int clipIndex, BlendDirection direction)
{
    mBlendNodes[(int)direction].PlayAnimation(mModelId, clipIndex, true);
}

void BlendedAnimator::UpdateWeights(float xWeight, float yWeight)
{
    mWeightX = CEMath::Clamp(xWeight, -1.0f, 1.0f);
    mWeightY = CEMath::Clamp(yWeight, -1.0f, 1.0f);
}
