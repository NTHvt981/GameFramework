#pragma once
#include "IFileSystem.h"
#include "FileSystem/DataTypes/FolderDirectory.h"
#include "FileSystem/DataTypes/FileDirectory.h"
#include "Core/DataTypes/Flag.h"
#include "Core/DataTypes/InitOnce.h"

namespace files
{
class FileSystem final : public IFileSystem
{
public:
	FileSystem();
	~FileSystem();
	void Initialize() override;
	// Inherited via IFileSystem
	void WriteTextFile(const FileId i_fileId) override;
	void ReadTextFile(const FileId i_fileId) override;
	data_types::String GetFileDirectory(const FileId i_fileId) const override;

private:
	data_types::String ToPath(const FolderDirectory& i_folderDirectory) const;
	data_types::String ToPath(const FileDirectory& i_fileDirectory) const;
	data_types::InitOnce<FolderDirectory> m_applicationFolderDirectory;
	data_types::Flag m_initializeFlag;
};

} // namespace files
