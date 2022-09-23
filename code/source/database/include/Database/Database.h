#pragma once
#include "IDatabase.h"
#include "FileSystem/IFileSystem.h"
#include <map>

namespace database
{

class Database final: public IDatabase
{
public:
	Database(std::shared_ptr<files::IFileSystem> i_fileSystem);
	void LoadResource() override;
	// IGraphicDatabaseAPI impl
	virtual std::weak_ptr<const graphics::Texture> GetTextureRef(const ids::TextureId i_textureId) override;
	virtual const graphics::Texture GetTexture(const ids::TextureId i_textureId) override;
	virtual std::weak_ptr<const graphics::SpriteDef> GetSpriteRef(const ids::SpriteId i_spriteId) override;
	virtual const graphics::SpriteDef GetSprite(const ids::SpriteId i_spriteId) override;
	virtual std::weak_ptr<const graphics::AnimationDef> GetAnimationRef(const ids::AnimationId i_animationId) override;
	virtual const graphics::AnimationDef GetAnimation(const ids::AnimationId i_animationId) override;

private:
	void LoadTextures();
	void LoadSprites();
	void LoadAnimation();
	std::shared_ptr<files::IFileSystem> m_fileSystem;

	std::map<ids::TextureId, std::shared_ptr<graphics::Texture>> m_textures;
	std::map<ids::SpriteId, std::shared_ptr<graphics::SpriteDef>> m_sprites;
	std::map<ids::AnimationId, std::shared_ptr<graphics::AnimationDef>> m_animations;
};

} // namespace database