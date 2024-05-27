#include "Logic/Databases/Database.h"
#include "Core/DataTypes/Folder.h"
#include "Xml/TexureParser.h"
#include "Xml/SpriteParser.h"
#include "Xml/AnimationParser.h"
#include "Xml/SoundParser.h"
#include "Core/DataTypes/Texture.h"
#include "Core/DataTypes/SpriteDef.h"
#include "Core/DataTypes/AnimationDef.h"
#include "AudioSystem/DataTypes/Sound.h"

namespace logic
{

////////////////////////////////////////////////////////////////////////////////

Database::Database(std::shared_ptr<IFileSystem> i_fileSystem)
	: m_fileSystem(i_fileSystem)
{
}

////////////////////////////////////////////////////////////////////////////////

void Database::LoadResource()
{
	LoadTextures();
	LoadSprites();
	LoadAnimations();
	LoadSounds();
}

////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<const core::Texture> Database::GetTextureRef(const core::TextureId i_textureId) const
{
	return m_textures.at(i_textureId);
}

////////////////////////////////////////////////////////////////////////////////

const core::Texture Database::GetTexture(const core::TextureId i_textureId) const
{
	return *m_textures.at(i_textureId).get();
}

////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<const core::SpriteDef> Database::GetSpriteRef(const core::SpriteId i_spriteId) const
{
	return m_sprites.at(i_spriteId);
}

////////////////////////////////////////////////////////////////////////////////

const core::SpriteDef Database::GetSprite(const core::SpriteId i_spriteId) const
{
	return *m_sprites.at(i_spriteId).get();
}

////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<const core::AnimationDef> Database::GetAnimationRef(const core::AnimationId i_animationId) const
{
	return m_animations.at(i_animationId);
}

////////////////////////////////////////////////////////////////////////////////

const core::AnimationDef Database::GetAnimation(const core::AnimationId i_animationId) const
{
	return *m_animations.at(i_animationId).get();
}

////////////////////////////////////////////////////////////////////////////////

core::Ref<audios::Sound> Database::GetSoundRef(const core::SoundId i_soundId) const
{
	return core::Ref<audios::Sound>(m_sounds.at(i_soundId).get());
}

////////////////////////////////////////////////////////////////////////////////

void Database::LoadTextures()
{
	const core::String path = m_fileSystem->GetTexturesXmlFilePath();
	const std::string stringPath = path.ToStdStr();
	std::vector<core::Texture> textures = xml::LoadTexturesFile(stringPath.c_str());

	for (core::Texture& texture : textures)
	{
		texture.filePath = m_fileSystem->GetTexturesFolderPath() + texture.filePath;
		m_textures.try_emplace(texture.id, std::make_shared<core::Texture>(texture));
	}
}

////////////////////////////////////////////////////////////////////////////////

void Database::LoadSprites()
{
	const core::String path = m_fileSystem->GetSpritesXmlFilePath();
	const std::string stringPath = path.ToStdStr();
	std::vector<core::SpriteDef> sprites = xml::LoadSpritesFile(stringPath.c_str());

	for (core::SpriteDef& sprite : sprites)
	{
		sprite.textureRef = GetTextureRef(sprite.textureId);
		m_sprites.try_emplace(sprite.id, std::make_shared<core::SpriteDef>(sprite));
	}
}

////////////////////////////////////////////////////////////////////////////////

void Database::LoadAnimations()
{
	const core::String path = m_fileSystem->GetAnimationsXmlFilePath();
	const std::string stringPath = path.ToStdStr();
	std::vector<core::AnimationDef> animations = xml::LoadAnimationsFile(stringPath.c_str());

	for (core::AnimationDef& animation : animations)
	{
		for (core::AnimationFrameDef& frame : animation.frames)
		{
			frame.spriteDefRef = GetSpriteRef(frame.spriteId);
		}
		m_animations.try_emplace(animation.id, std::make_shared<core::AnimationDef>(animation));
	}
}

////////////////////////////////////////////////////////////////////////////////

void Database::LoadSounds()
{
	const core::String path = m_fileSystem->GetSoundsXmlFilePath();
	const std::string stringPath = path.ToStdStr();
	std::vector<audios::Sound> sounds = xml::LoadSoundsFile(stringPath.c_str());

	for (audios::Sound& sound : sounds)
	{
		sound.filePath = m_fileSystem->GetSoundsFolderPath() + sound.filePath;
		m_sounds.try_emplace(sound.id, std::make_shared<audios::Sound>(sound));
	}
}

////////////////////////////////////////////////////////////////////////////////

} // namespace logic