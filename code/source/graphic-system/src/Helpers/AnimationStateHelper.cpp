#include "GraphicSystem/Helpers/AnimationStateHelper.h"

namespace graphics
{

void SetAnimationDef(AnimationState& i_animationState, std::shared_ptr<const AnimationDef> i_animationDef)
{
    i_animationState.animationDef = i_animationDef;
    const AnimationFrameDef& currentFrame = i_animationDef->frames[i_animationState.currentFrameIndex];
    i_animationState.spriteStateRef->spriteDef = currentFrame.spriteDefRef;
}

void UpdateAnimationState(AnimationState& animationState, const core::Duration& dt)
{
    if (animationState.pause)
    {
        return;
    }

    uint64_t& currentFrameIndex = animationState.currentFrameIndex;
    core::Duration& currentDuration = animationState.currentDuration;
    auto animationDef = animationState.animationDef.lock();

    core::Duration newDuration = currentDuration + dt;
    const AnimationFrameDef& currentFrame = animationDef->frames[currentFrameIndex];
    if (newDuration >= currentFrame.duration)
    {
        currentDuration = newDuration - currentFrame.duration;
        currentFrameIndex++;
        auto frameSize = animationDef->frames.size();
        if (currentFrameIndex >= frameSize)
        {
            animationState.sig_onAnimationFinished.Emit();
            if (animationState.loop)
            {
                currentFrameIndex = currentFrameIndex - frameSize;
            }
            else
            {
                currentFrameIndex = frameSize - 1;
            }
        }

        const AnimationFrameDef& newFrame = animationDef->frames[currentFrameIndex];
        animationState.spriteStateRef->spriteDef = newFrame.spriteDefRef;
    }
    else
    {
        currentDuration = newDuration;
    }
}

std::weak_ptr<const SpriteDef> GetCurrentSpriteDefFromAnimationState(const AnimationState& animationState)
{
    std::shared_ptr<const AnimationDef> animationDef = animationState.animationDef.lock();
    return animationDef->frames[animationState.currentFrameIndex].spriteDefRef;
}

} // namespace graphics