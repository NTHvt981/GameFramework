#pragma once
#include "GraphicSystem/DataTypes/Texture.h"
#include "GraphicSystem/DataTypes/AnimationDef.h"
#include "GraphicSystem/DataTypes/SpriteDef.h"
#include <memory>

namespace graphics::database
{

class IGraphicDatabaseAPI
{
public:
	virtual std::weak_ptr<const Texture> GetTextureRef(const core::TextureId i_textureId) = 0;
	virtual const Texture GetTexture(const core::TextureId i_textureId) = 0;
	virtual std::weak_ptr<const SpriteDef> GetSpriteRef(const core::SpriteId i_spriteId) = 0;
	virtual const SpriteDef GetSprite(const core::SpriteId i_spriteId) = 0;
	virtual std::weak_ptr<const AnimationDef> GetAnimationRef(const core::AnimationId i_animationId) = 0;
	virtual const AnimationDef GetAnimation(const core::AnimationId i_animationId) = 0;
};

}