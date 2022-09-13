#pragma once
#include "Core/Identifiers/AnimationId.h"
#include "Core/Identifiers/SpriteId.h"
#include "Core/Identifiers/RenderLayer.h"
#include "DataTypes/Texture.h"
#include "DataTypes/SpriteState.h"
#include "DataTypes/AnimationState.h"
#include <memory>

namespace graphics
{

class IGraphicsSystem
{
public:
	virtual std::weak_ptr<SpriteState> RegisterDraw(
		const ids::SpriteId i_spriteId, 
		const ids::RenderLayer i_renderLayer = ids::RenderLayer::Default
	) = 0;
	virtual void DeregisterDraw(
		std::weak_ptr<SpriteState> i_spriteState
	) = 0;
	virtual std::weak_ptr<AnimationState> RegisterDraw(
		const ids::AnimationId i_animationId, 
		const ids::RenderLayer i_renderLayer = ids::RenderLayer::Default
	) = 0;
	virtual void DeregisterDraw(
		std::weak_ptr<AnimationState> i_animationState
	) = 0;
	virtual void SetRenderLayer(
		const SpriteState::Id i_spriteStateId,
		const ids::RenderLayer i_renderLayer = ids::RenderLayer::Default
	) = 0;

private:

};

} // namespace graphics