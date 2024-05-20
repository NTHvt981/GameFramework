#include "GraphicSystem/Helpers/AnimationStateHelper.h"

namespace graphics
{

void UpdateAnimationState(AnimationState& animationState, const core::Duration& dt)
{
    if (animationState.pause)
    {
        return;
    }

    uint64_t& currentFrameIndex = animationState.currentFrameIndex;
    core::Duration& currentDuration = animationState.currentDuration;
    auto animationDef = animationState.animationDef.lock();

    const core::Duration calculatedDt = dt * animationState.speed;
    core::Duration newDuration = currentDuration + calculatedDt;
    const AnimationFrameDef& currentFrame = animationDef->frames[currentFrameIndex];
    if (newDuration >= currentFrame.duration)
    {
        currentDuration = newDuration - currentFrame.duration;
        currentFrameIndex++;
        auto frameSize = animationDef->frames.size();
        if (currentFrameIndex >= frameSize)
        {
            if (animationState.loop)
            {
                currentFrameIndex = 0;
                animationState.sig_onAnimationFinished.Emit();
            }
            else
            {
                if (!animationState.hasFinished)
                {
                    animationState.sig_onAnimationFinished.Emit();
                    animationState.hasFinished = true;
                }
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

} // namespace graphics