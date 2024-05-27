#pragma once
#include "IDatabase.h"
#include "Logic/LogicSystems/IFileSystem.h"
#include <map>

namespace logic
{

class Database final: public IDatabase
{
public:
	Database(std::shared_ptr<IFileSystem> i_fileSystem);
	void LoadResource() override;

	// IGraphicDatabaseAPI impl
	virtual std::weak_ptr<const core::Texture> GetTextureRef(const core::TextureId i_textureId) const override;
	virtual const core::Texture GetTexture(const core::TextureId i_textureId) const override;
	virtual std::weak_ptr<const core::SpriteDef> GetSpriteRef(const core::SpriteId i_spriteId) const override;
	virtual const core::SpriteDef GetSprite(const core::SpriteId i_spriteId) const override;
	virtual std::weak_ptr<const core::AnimationDef> GetAnimationRef(const core::AnimationId i_animationId) const override;
	virtual const core::AnimationDef GetAnimation(const core::AnimationId i_animationId) const override;

	// IAudioDatabaseAPI impl
	core::Ref<core::Sound> GetSoundRef(const core::SoundId i_soundId) const override;

private:
	void LoadTextures();
	void LoadSprites();
	void LoadAnimations();
	void LoadSounds();
	std::shared_ptr<logic::IFileSystem> m_fileSystem;

	std::map<core::TextureId, std::shared_ptr<core::Texture>> m_textures;
	std::map<core::SpriteId, std::shared_ptr<core::SpriteDef>> m_sprites;
	std::map<core::AnimationId, std::shared_ptr<core::AnimationDef>> m_animations;

	std::map<core::SoundId, std::shared_ptr<core::Sound>> m_sounds;
};

} // namespace logic