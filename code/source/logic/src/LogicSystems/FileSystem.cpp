#include "Logic/LogicSystems/FileSystem.h"
#include "Core/DataTypes/Folder.h"
#include "Core/DataTypes/FolderDirectory.h"
#include "Core/DataTypes/FileDirectory.h"
#include "Core/DataTypes/Flag.h"
#include "Core/DataTypes/InitOnce.h"
#include "Core/DataTypes/String.h"
#include <windows.h>

core::String GetApplicationFolderPath(const core::String& i_demiliter);

namespace logic
{

const core::Folder sk_dataFolder{ "data" };
const core::Folder sk_xmlFolder{ "Xml" };
const core::Folder sk_texturesFolder{ "Textures" };
const core::Folder sk_soundsFolder{ "Sounds" };
const core::Folder sk_spritesFolder{ "Sprites" };
const core::File sk_texturesXmlFile{ "Textures", core::extXml };
const core::File sk_spritesXmlFile{ "Sprites", core::extXml };
const core::File sk_animationsXmlFile{ "Animations", core::extXml };
const core::File sk_soundsXmlFile{ "Sounds", core::extXml };
core::Flag s_initFlag;
core::FolderDirectory s_applicationFolderDirectory{};

////////////////////////////////////////////////////////////////////////////////

FileSystem::FileSystem()
{
}

////////////////////////////////////////////////////////////////////////////////

FileSystem::~FileSystem()
{

}

////////////////////////////////////////////////////////////////////////////////

void FileSystem::Initialize()
{
	s_initFlag.Set();

	const core::String applicationFolderPath = GetApplicationFolderPath("\\");

	core::FolderDirectory newValue({});
	newValue.SetFolders(applicationFolderPath);
	s_applicationFolderDirectory = newValue;
}

////////////////////////////////////////////////////////////////////////////////

void FileSystem::Shutdown()
{
}

////////////////////////////////////////////////////////////////////////////////

core::String FileSystem::GetAbsolutePath(const core::String i_relativePath) const
{
	return s_applicationFolderDirectory.ToString() + i_relativePath;
}

////////////////////////////////////////////////////////////////////////////////

core::String FileSystem::GetTexturesXmlFilePath() const
{
	core::FileDirectory result
	{
		s_applicationFolderDirectory + core::FolderDirectory{sk_dataFolder, sk_xmlFolder},
		sk_texturesXmlFile
	};
	return result.ToString();
}

////////////////////////////////////////////////////////////////////////////////

core::String FileSystem::GetSpritesXmlFilePath() const
{
	core::FileDirectory result
	{
		s_applicationFolderDirectory + core::FolderDirectory{sk_dataFolder, sk_xmlFolder},
		sk_spritesXmlFile
	};
	return result.ToString();
}

////////////////////////////////////////////////////////////////////////////////

core::String FileSystem::GetAnimationsXmlFilePath() const
{
	core::FileDirectory result
	{
		s_applicationFolderDirectory + core::FolderDirectory{sk_dataFolder, sk_xmlFolder},
		sk_animationsXmlFile
	};
	return result.ToString();
}

////////////////////////////////////////////////////////////////////////////////

core::String FileSystem::GetSoundsXmlFilePath() const
{
	core::FileDirectory result
	{
		s_applicationFolderDirectory + core::FolderDirectory{sk_dataFolder, sk_xmlFolder},
		sk_soundsXmlFile
	};
	return result.ToString();
}

////////////////////////////////////////////////////////////////////////////////

core::String FileSystem::GetTexturesFolderPath() const
{
	core::FolderDirectory result = s_applicationFolderDirectory + core::FolderDirectory{ sk_dataFolder, sk_texturesFolder };
	return result.ToString();
}

////////////////////////////////////////////////////////////////////////////////

core::String FileSystem::GetSoundsFolderPath() const
{
	core::FolderDirectory result = s_applicationFolderDirectory + core::FolderDirectory{ sk_dataFolder, sk_soundsFolder };
	return result.ToString();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace logic

core::String GetApplicationFolderPath(const core::String& i_demiliter)
{
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);

	core::String result(buffer);
	std::wstring::size_type pos = result.FindLastOf(i_demiliter);
	return core::String(buffer).SubString(0, pos);
}