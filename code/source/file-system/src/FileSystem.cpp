#include "stdafx.h"
#include "FileSystem/DataTypes/Folder.h"
#include "FileSystem/FileSystem.h"
#include "FileSystem/DataTypes/FolderDirectory.h"
#include "FileSystem/DataTypes/FileDirectory.h"
#include "Core/Identifiers/FileId.h"
#include "Core/DataTypes/Flag.h"
#include "Core/DataTypes/InitOnce.h"
#include "Core/DataTypes/String.h"
#include <windows.h>

core::String GetApplicationFolderPath(const core::String& i_demiliter);

namespace files
{

core::Flag s_initFlag;
core::InitOnce<FolderDirectory> s_applicationFolderDirectory;

////////////////////////////////////////////////////////////////////////////////

FileSystem::FileSystem()
{
	Folder textureFolder{ "Textures" };
	Folder dataFolder{ "data" };
	FolderDirectory textureDir{ BackwardFolder, dataFolder, textureFolder };
	m_mapFileDirectories = {
		{
			ids::FileId::EnemiesTexture,
			FileDirectory {
				textureDir, File{"enemies", extPng}
			}
		},
		{
			ids::FileId::PlayerTexture,
			FileDirectory {
				textureDir, File{"PlayerSheetTransparent", extPng}
			}
		},
		{
			ids::FileId::PlayerHealthTexture,
			FileDirectory {
				textureDir, File{"Player health", extPng}
			}
		},
		{
			ids::FileId::OtherObjectsTexture,
			FileDirectory {
				textureDir, File{"OtherObjects", extPng}
			}
		},
		{
			ids::FileId::BlackScreenTexture,
			FileDirectory {
				textureDir, File{"BlackScreen", extPng}
			}
		},
		{
			ids::FileId::BossTexture,
			FileDirectory {
				textureDir, File{"Boss", extPng}
			}
		},
		{
			ids::FileId::OpeningTexture,
			FileDirectory {
				textureDir, File{"Opening", extPng}
			}
		},
		{
			ids::FileId::BlackScreenTexture,
			FileDirectory {
				textureDir, File{"RollOut", extPng}
			}
		},
		{
			ids::FileId::ItemTexture,
			FileDirectory {
				textureDir, File{"Items", extPng}
			}
		},
		{
			ids::FileId::CollisionDebugTexture,
			FileDirectory {
				textureDir, File{"bbox", extPng}
			}
		},
	};
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
	s_applicationFolderDirectory.Set(newValue);
	FolderDirectory dataFolderPath{  };

	for (auto& [id, fileDirectory] : m_mapFileDirectories)
	{
		fileDirectory.folderDirectory = s_applicationFolderDirectory.Get() + fileDirectory.folderDirectory;
	}
}

////////////////////////////////////////////////////////////////////////////////

void FileSystem::ShutDown()
{
}

////////////////////////////////////////////////////////////////////////////////

void FileSystem::WriteTextFile(const ids::FileId i_fileId)
{
}

////////////////////////////////////////////////////////////////////////////////

void FileSystem::ReadTextFile(const ids::FileId i_fileId)
{
}

////////////////////////////////////////////////////////////////////////////////

core::String FileSystem::GetFileDirectory(const ids::FileId i_fileId) const
{
	if (m_mapFileDirectories.find(i_fileId) == m_mapFileDirectories.end())
	{
		throw("Invalid FileId, can not find directory for %d", i_fileId);
	}

	const FileDirectory& fileDirectory = m_mapFileDirectories.at(i_fileId);
	return fileDirectory.ToString();
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