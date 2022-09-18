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

class ISpriteGraphicAPI
{
public:
	virtual std::weak_ptr<SpriteState> RegisterSprite(
		const ids::SpriteId i_spriteId,
		const ids::RenderLayer i_renderLayer = ids::RenderLayer::Default
	) = 0;
	virtual void DeregisterSprite(
		const SpriteState::Id i_spriteStateId
	) = 0;
	virtual void SetSpriteRenderLayer(
		const SpriteState::Id i_spriteStateId,
		const ids::RenderLayer i_renderLayer
	) = 0;
};

} // namespace graphics