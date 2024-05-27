#pragma once
#include "Core/Identifiers/TextureId.h"
#include "Core/Identifiers/SpriteId.h"
#include "Core/Identifiers/AnimationId.h"
#include <memory>

namespace core
{
struct Texture;
struct SpriteDef;
struct AnimationDef;
} // namespace core

namespace logic
{

class IGraphicDatabaseAPI
{
public:
	virtual std::weak_ptr<const core::Texture> GetTextureRef(const core::TextureId i_textureId) const = 0;
	virtual const core::Texture GetTexture(const core::TextureId i_textureId) const = 0;
	virtual std::weak_ptr<const core::SpriteDef> GetSpriteRef(const core::SpriteId i_spriteId) const = 0;
	virtual const core::SpriteDef GetSprite(const core::SpriteId i_spriteId) const = 0;
	virtual std::weak_ptr<const core::AnimationDef> GetAnimationRef(const core::AnimationId i_animationId) const = 0;
	virtual const core::AnimationDef GetAnimation(const core::AnimationId i_animationId) const = 0;
};

} // namespace logic