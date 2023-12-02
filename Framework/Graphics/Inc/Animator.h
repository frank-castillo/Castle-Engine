#pragma once
#include "ModelManager.h"
#include "Bone.h"

namespace CASTLEEngine::Graphics
{
    class BlendNode
    {
    public:
        void PlayAnimation(ModelId id, int clipIndex, bool looping);
        void Update(float deltaTime);
        bool GetToParentTransform(const Bone* bone, Transform& transform) const;

        bool IsFinished() const;
        float GetAnimationTick() const { return mAnimationTick; }
        int GetClipIndex() const { return mClipIndex; }
        bool IsLooping() const { return mLooping; }
        
        BlendNode() = default;
        // delete copies
        BlendNode(BlendNode&) = delete;
        BlendNode& operator=(BlendNode&) = delete;
        //Override moves
        BlendNode(BlendNode&& rhs) noexcept;
        BlendNode& operator=(BlendNode&& rhs) noexcept;

    private:
        ModelId mModelId = 0;
        int mClipIndex = -1;
        float mAnimationTick = 0.0f;
        bool mLooping = false;
    };

    class Animator
    {
    public:
        void Initialize(ModelId id);
        virtual void PlayAnimation(int clipIndex, bool looping, float blendDuration = 0.0f);
        virtual void Update(float deltaTime);
        bool IsFinished();

        size_t GetAnimationCount() const;
        virtual CEMath::Matrix4 GetToParentTransform(const Bone* bone) const;

    protected:
        ModelId mModelId = 0;
        float mBlendDuration = -1.0f;
        float mBlendTime = -1.0f;

        BlendNode mCurrentAnimation;
        BlendNode mNextAnimation;
    };

    class BlendedAnimator : public Animator
    {
    public:
        enum class BlendDirection
        {
            Center,
            North,
            South,
            East,
            West
        };

        void PlayAnimation(int clipIndex, bool looping, float blendDuration) override;
        void Update(float deltaTime) override;
        CEMath::Matrix4 GetToParentTransform(const Bone* bone) const override;

        void SetAnimation(int mClipIndex, BlendDirection direction);
        void UpdateWeights(float xWeight, float yWeight);

    private:
        BlendNode mBlendNodes[5];
        float mWeightX = 0.0f;
        float mWeightY = 0.0f;
    };
}