#pragma once
#include "Core/Identifiers/TextureId.h"
#include "Core/Identifiers/SpriteId.h"
#include "Core/Identifiers/AnimationId.h"
#include <memory>

namespace graphics
{
struct Texture;
struct SpriteDef;
struct AnimationDef;
} // namespace graphics

namespace graphics::database
{

class IGraphicDatabaseAPI
{
public:
	virtual std::weak_ptr<const Texture> GetTextureRef(const core::TextureId i_textureId) const = 0;
	virtual const Texture GetTexture(const core::TextureId i_textureId) const = 0;
	virtual std::weak_ptr<const SpriteDef> GetSpriteRef(const core::SpriteId i_spriteId) const = 0;
	virtual const SpriteDef GetSprite(const core::SpriteId i_spriteId) const = 0;
	virtual std::weak_ptr<const AnimationDef> GetAnimationRef(const core::AnimationId i_animationId) const = 0;
	virtual const AnimationDef GetAnimation(const core::AnimationId i_animationId) const = 0;
};

}