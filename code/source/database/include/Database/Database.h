#pragma once
#include "IDatabase.h"

namespace database
{

class Database final: public IDatabase
{
public:
	// IGraphicDatabaseAPI impl
	virtual std::weak_ptr<const graphics::Texture> GetTextureRef(const ids::TextureId i_textureId) override;
	virtual const graphics::Texture GetTexture(const ids::TextureId i_textureId) override;
	virtual std::weak_ptr<const graphics::SpriteDef> GetSpriteRef(const ids::SpriteId i_spriteId) override;
	virtual const graphics::SpriteDef GetSprite(const ids::SpriteId i_spriteId) override;
	virtual std::weak_ptr<const graphics::AnimationDef> GetAnimationRef(const ids::AnimationId i_animationId) override;
	virtual const graphics::AnimationDef GetAnimation(const ids::AnimationId i_animationId) override;

private:
	std::vector<std::shared_ptr<graphics::Texture>> m_textures;
	std::vector<std::shared_ptr<graphics::SpriteDef>> m_sprites;
	std::vector<std::shared_ptr<graphics::AnimationDef>> m_animations;
};

} // namespace database