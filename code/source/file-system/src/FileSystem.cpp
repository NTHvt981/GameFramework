#include "stdafx.h"
#include "FileSystem/FileSystem.h"
#include "FileSystem/DataTypes/FolderDirectory.h"
#include "FileSystem/DataTypes/FileDirectory.h"
#include "Core/DataTypes/Flag.h"
#include "Core/DataTypes/InitOnce.h"
#include <windows.h>

data_types::String GetApplicationFolderPath(const data_types::String& i_demiliter);

namespace files
{

////////////////////////////////////////////////////////////////////////////////

FileSystem::FileSystem()
	: m_applicationFolderDirectory(std::make_unique<data_types::InitOnce<FolderDirectory>>())
	, m_initializeFlag(std::make_unique<data_types::Flag>())
{
	Folder textureFolder{"Texture"};
	m_mapFileDirectories = {
		{
			ids::FileId::EnemiesTexture,
			FileDirectory {
				FolderDirectory{BackwardFolder, textureFolder},
				File{"enemies", "png"}
			}
		},
		{
			ids::FileId::PlayerTexture,
			FileDirectory {
				FolderDirectory{BackwardFolder, textureFolder},
				File{"PlayerSheetTransparent", "png"}
			}
		},
		{
			ids::FileId::PlayerHealthTexture,
			FileDirectory {
				FolderDirectory{BackwardFolder, textureFolder},
				File{"Player health", "png"}
			}
		},
		{
			ids::FileId::OtherObjectsTexture,
			FileDirectory {
				FolderDirectory{BackwardFolder, textureFolder},
				File{"OtherObjects", "png"}
			}
		},
		{
			ids::FileId::BlackScreenTexture,
			FileDirectory {
				FolderDirectory{BackwardFolder, textureFolder},
				File{"BlackScreen", "png"}
			}
		},
		{
			ids::FileId::BossTexture,
			FileDirectory {
				FolderDirectory{BackwardFolder, textureFolder},
				File{"Boss", "png"}
			}
		},
		{
			ids::FileId::OpeningTexture,
			FileDirectory {
				FolderDirectory{BackwardFolder, textureFolder},
				File{"Opening", "png"}
			}
		},
		{
			ids::FileId::BlackScreenTexture,
			FileDirectory {
				FolderDirectory{BackwardFolder, textureFolder},
				File{"RollOut", "png"}
			}
		},
		{
			ids::FileId::ItemTexture,
			FileDirectory {
				FolderDirectory{BackwardFolder, textureFolder},
				File{"Items", "png"}
			}
		},
		{
			ids::FileId::CollisionDebugTexture,
			FileDirectory {
				FolderDirectory{BackwardFolder, textureFolder},
				File{"bbox", "png"}
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
	m_initializeFlag->Set();

	const data_types::String applicationFolderPath = GetApplicationFolderPath("\\");

	FolderDirectory newValue({});
	newValue.SetFolders(applicationFolderPath);
	m_applicationFolderDirectory->Set(newValue);

	for (auto& [id, fileDirectory] : m_mapFileDirectories)
	{
		fileDirectory.folderDirectory =  m_applicationFolderDirectory->Get() + fileDirectory.folderDirectory;
	}
}

////////////////////////////////////////////////////////////////////////////////

void Initialize()
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

data_types::String FileSystem::GetFileDirectory(const ids::FileId i_fileId) const
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

data_types::String GetApplicationFolderPath(const data_types::String& i_demiliter)
{
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);

	data_types::String result(buffer);
	std::wstring::size_type pos = result.FindLastOf(i_demiliter);
	return data_types::String(buffer).SubString(0, pos);
}