#include "GraphicSystem/Helpers/AnimationStateHelper.h"

namespace graphics
{

void SetAnimationDef(AnimationState& i_animationState, std::shared_ptr<const AnimationDef> i_animationDef)
{
    i_animationState.animationDef = i_animationDef;
    const AnimationFrameDef& currentFrame = i_animationDef->frames[i_animationState.currentFrameIndex];
    i_animationState.spriteStateRef->spriteDef = currentFrame.spriteDefRef;
}

void UpdateAnimationState(AnimationState& animationState, uint64_t dt)
{
    if (animationState.pause)
    {
        return;
    }

    uint64_t& currentFrameIndex = animationState.currentFrameIndex;
    uint64_t& currentFrameTime = animationState.currentFrameTime;
    auto animationDef = animationState.animationDef.lock();

    uint64_t newFrameTime = currentFrameTime + dt;
    const AnimationFrameDef& currentFrame = animationDef->frames[currentFrameIndex];
    if (newFrameTime >= currentFrame.duration)
    {
        currentFrameTime = newFrameTime - currentFrame.duration;
        currentFrameIndex++;
        auto frameSize = animationDef->frames.size();
        if (currentFrameIndex >= frameSize)
        {
            if (animationState.loop)
            {
                currentFrameIndex = currentFrameIndex - frameSize;
                animationState.sig_onAnimationFinished.Emit();
            }
        }

        const AnimationFrameDef& newFrame = animationDef->frames[currentFrameIndex];
        animationState.spriteStateRef->spriteDef = newFrame.spriteDefRef;
    }
    else
    {
        currentFrameTime = newFrameTime;
    }
}

std::weak_ptr<const SpriteDef> GetCurrentSpriteDefFromAnimationState(const AnimationState& animationState)
{
    std::shared_ptr<const AnimationDef> animationDef = animationState.animationDef.lock();
    return animationDef->frames[animationState.currentFrameIndex].spriteDefRef;
}

} // namespace graphics