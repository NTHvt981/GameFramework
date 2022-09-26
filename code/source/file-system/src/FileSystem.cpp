#include "stdafx.h"
#include "FileSystem/DataTypes/Folder.h"
#include "FileSystem/FileSystem.h"
#include "FileSystem/DataTypes/FolderDirectory.h"
#include "FileSystem/DataTypes/FileDirectory.h"
#include "Core/DataTypes/Flag.h"
#include "Core/DataTypes/InitOnce.h"
#include "Core/DataTypes/String.h"
#include <windows.h>

core::String GetApplicationFolderPath(const core::String& i_demiliter);

namespace files
{

const Folder sk_dataFolder{ "data" };
const Folder sk_xmlFolder{ "Xml" };
const Folder sk_texturesFolder{ "Textures" };
const Folder sk_spritesFolder{ "Sprites" };
const File sk_texturesXmlFile{ "Textures", files::extXml };
const File sk_spritesXmlFile{ "Sprites", files::extXml };
const File sk_animationsXmlFile{ "Animations", files::extXml };
core::Flag s_initFlag;
FolderDirectory s_applicationFolderDirectory{};

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

	FolderDirectory newValue({});
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
	FileDirectory result
	{
		s_applicationFolderDirectory + FolderDirectory{sk_dataFolder, sk_xmlFolder},
		sk_texturesXmlFile
	};
	return result.ToString();
}

////////////////////////////////////////////////////////////////////////////////

core::String FileSystem::GetSpritesXmlFilePath() const
{
	FileDirectory result
	{
		s_applicationFolderDirectory + FolderDirectory{sk_dataFolder, sk_xmlFolder},
		sk_spritesXmlFile
	};
	return result.ToString();
}

////////////////////////////////////////////////////////////////////////////////

core::String FileSystem::GetAnimationsXmlFilePath() const
{
	FileDirectory result
	{
		s_applicationFolderDirectory + FolderDirectory{sk_dataFolder, sk_xmlFolder},
		sk_animationsXmlFile
	};
	return result.ToString();
}

////////////////////////////////////////////////////////////////////////////////

core::String FileSystem::GetTexturesFolderPath() const
{
	FolderDirectory result = s_applicationFolderDirectory + FolderDirectory{ sk_dataFolder, sk_texturesFolder };
	return result.ToString();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace files

core::String GetApplicationFolderPath(const core::String& i_demiliter)
{
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);

	core::String result(buffer);
	std::wstring::size_type pos = result.FindLastOf(i_demiliter);
	return core::String(buffer).SubString(0, pos);
}