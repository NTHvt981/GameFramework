#pragma once
#include "GraphicSystem/DataTypes/SpriteState.h"
#include "Core/Identifiers/RenderLayer.h"
#include <memory>

namespace graphics
{

class ISpriteGraphicAPI
{
public:
	virtual SpriteState::Id GenerateSpriteStateId() = 0;
	virtual void RegisterSprite(std::shared_ptr<SpriteState> i_spriteState) = 0;
	virtual void DeregisterSprite(const SpriteState::Id i_spriteStateId) = 0;
	virtual void SetSpriteRenderLayer(
		const SpriteState::Id i_spriteStateId,
		const core::RenderLayer i_renderLayer
	) = 0;
};

} // namespace graphics