#pragma once
#include "Core/DataTypes/AnimationState.h"
#include "Core/Identifiers/RenderLayer.h"
#include <memory>

namespace core
{

class IAnimationGraphicAPI
{
public:
	virtual AnimationState::Id GenerateAnimationStateId() = 0;
	virtual void RegisterAnimation(std::shared_ptr<AnimationState> i_animationState) = 0;
	virtual void DeregisterAnimation(const AnimationState::Id i_animationStateId) = 0;
	virtual void SetAnimationRenderLayer(
		const AnimationState::Id i_animationStateId,
		const RenderLayer i_renderLayer
	) = 0;
};

} // namespace core