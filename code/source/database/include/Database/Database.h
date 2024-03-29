#pragma once
#include "IDatabase.h"
#include <map>

namespace files
{
class IFileSystem;
} // namespace files

namespace database
{

class Database final: public IDatabase
{
public:
	Database(std::shared_ptr<files::IFileSystem> i_fileSystem);
	void LoadResource() override;
	// IGraphicDatabaseAPI impl
	virtual std::weak_ptr<const graphics::Texture> GetTextureRef(const core::TextureId i_textureId) const override;
	virtual const graphics::Texture GetTexture(const core::TextureId i_textureId) const override;
	virtual std::weak_ptr<const graphics::SpriteDef> GetSpriteRef(const core::SpriteId i_spriteId) const override;
	virtual const graphics::SpriteDef GetSprite(const core::SpriteId i_spriteId) const override;
	virtual std::weak_ptr<const graphics::AnimationDef> GetAnimationRef(const core::AnimationId i_animationId) const override;
	virtual const graphics::AnimationDef GetAnimation(const core::AnimationId i_animationId) const override;

	// IAudioDatabaseAPI impl
	core::Ref<audios::Sound> GetSoundRef(const core::SoundId i_soundId) const override;

private:
	void LoadTextures();
	void LoadSprites();
	void LoadAnimations();
	void LoadSounds();
	std::shared_ptr<files::IFileSystem> m_fileSystem;

	std::map<core::TextureId, std::shared_ptr<graphics::Texture>> m_textures;
	std::map<core::SpriteId, std::shared_ptr<graphics::SpriteDef>> m_sprites;
	std::map<core::AnimationId, std::shared_ptr<graphics::AnimationDef>> m_animations;

	std::map<core::SoundId, std::shared_ptr<audios::Sound>> m_sounds;
};

} // namespace database