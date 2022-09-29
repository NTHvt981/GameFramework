#pragma once
#include "Core/Identifiers/AnimationId.h"
#include "Core/Identifiers/SpriteId.h"
#include "Core/Identifiers/RenderLayer.h"
#include "GraphicSystem/DataTypes/Texture.h"
#include "GraphicSystem/DataTypes/SpriteState.h"
#include "GraphicSystem/DataTypes/AnimationState.h"
#include <memory>

namespace graphics
{

class IAnimationGraphicAPI
{
public:
	virtual AnimationState::Id GenerateAnimationStateId() = 0;
	virtual void RegisterAnimation(std::shared_ptr<AnimationState> i_animationState) = 0;
	virtual void DeregisterAnimation(const AnimationState::Id i_animationStateId) = 0;
	virtual void SetAnimationRenderLayer(
		const AnimationState::Id i_animationStateId,
		const core::RenderLayer i_renderLayer
	) = 0;
};

} // namespace graphics