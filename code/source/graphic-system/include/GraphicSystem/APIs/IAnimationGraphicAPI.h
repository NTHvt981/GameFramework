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
	virtual std::weak_ptr<AnimationState> RegisterAnimation(
		const ids::AnimationId i_animationId,
		const ids::RenderLayer i_renderLayer = ids::RenderLayer::Default
	) = 0;
	virtual void DeregisterAnimation(
		std::weak_ptr<AnimationState> i_animationState
	) = 0;
	virtual void SetAnimationRenderLayer(
		const AnimationState::Id i_animationStateId,
		const ids::RenderLayer i_oldRenderLayer,
		const ids::RenderLayer i_newRenderLayer
	) = 0;
};

} // namespace graphics