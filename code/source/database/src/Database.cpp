#include "Database/Database.h"
#include "FileSystem/IFileSystem.h"
#include "FileSystem/DataTypes/Folder.h"
#include "Xml/TexureParser.h"
#include "Xml/SpriteParser.h"
#include "Xml/AnimationParser.h"
#include "GraphicSystem/DataTypes/Texture.h"
#include "GraphicSystem/DataTypes/SpriteDef.h"
#include "GraphicSystem/DataTypes/AnimationDef.h"

namespace database
{

////////////////////////////////////////////////////////////////////////////////

Database::Database(std::shared_ptr<files::IFileSystem> i_fileSystem)
	: m_fileSystem(i_fileSystem)
{
}

////////////////////////////////////////////////////////////////////////////////

void Database::LoadResource()
{
	LoadTextures();
	LoadSprites();
	LoadAnimation();
}

////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<const graphics::Texture> Database::GetTextureRef(const core::TextureId i_textureId) const
{
	return m_textures.at(i_textureId);
}

////////////////////////////////////////////////////////////////////////////////

const graphics::Texture Database::GetTexture(const core::TextureId i_textureId) const
{
	return *m_textures.at(i_textureId).get();
}

////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<const graphics::SpriteDef> Database::GetSpriteRef(const core::SpriteId i_spriteId) const
{
	return m_sprites.at(i_spriteId);
}

////////////////////////////////////////////////////////////////////////////////

const graphics::SpriteDef Database::GetSprite(const core::SpriteId i_spriteId) const
{
	return *m_sprites.at(i_spriteId).get();
}

////////////////////////////////////////////////////////////////////////////////

std::weak_ptr<const graphics::AnimationDef> Database::GetAnimationRef(const core::AnimationId i_animationId) const
{
	return m_animations.at(i_animationId);
}

////////////////////////////////////////////////////////////////////////////////

const graphics::AnimationDef Database::GetAnimation(const core::AnimationId i_animationId) const
{
	return *m_animations.at(i_animationId).get();
}

////////////////////////////////////////////////////////////////////////////////

void Database::LoadTextures()
{
	const core::String path = m_fileSystem->GetTexturesXmlFilePath();
	const std::string stringPath = path.ToStdStr();
	std::vector<graphics::Texture> textures = xml::LoadTexturesFile(stringPath.c_str());

	for (graphics::Texture& texture : textures)
	{
		texture.filePath = m_fileSystem->GetTexturesFolderPath() + texture.filePath;
		m_textures.try_emplace(texture.id, std::make_shared<graphics::Texture>(texture));
	}
}

////////////////////////////////////////////////////////////////////////////////

void Database::LoadSprites()
{
	const core::String path = m_fileSystem->GetSpritesXmlFilePath();
	const std::string stringPath = path.ToStdStr();
	std::vector<graphics::SpriteDef> sprites = xml::LoadSpritesFile(stringPath.c_str());

	for (graphics::SpriteDef& sprite : sprites)
	{
		sprite.textureRef = GetTextureRef(sprite.textureId);
		m_sprites.try_emplace(sprite.id, std::make_shared<graphics::SpriteDef>(sprite));
	}
}

////////////////////////////////////////////////////////////////////////////////

void Database::LoadAnimation()
{
	const core::String path = m_fileSystem->GetAnimationsXmlFilePath();
	const std::string stringPath = path.ToStdStr();
	std::vector<graphics::AnimationDef> animations = xml::LoadAnimationsFile(stringPath.c_str());

	for (graphics::AnimationDef& animation : animations)
	{
		for (graphics::AnimationFrameDef& frame : animation.frames)
		{
			frame.spriteDefRef = GetSpriteRef(frame.spriteId);
		}
		m_animations.try_emplace(animation.id, std::make_shared<graphics::AnimationDef>(animation));
	}
}

////////////////////////////////////////////////////////////////////////////////

} // namespace database