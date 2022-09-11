#pragma once
#include "IFileSystem.h"
#include "FileSystem/DataTypes/FolderDirectory.h"
#include "FileSystem/DataTypes/FileDirectory.h"
#include "Core/DataTypes/Flag.h"
#include "Core/DataTypes/InitOnce.h"

#include <unordered_map>

namespace files
{
class FileSystem final : public IFileSystem
{

public:
	FileSystem();
	~FileSystem();
	void Initialize() override;
	// Inherited via IFileSystem
	void WriteTextFile(const ids::FileId i_fileId) override;
	void ReadTextFile(const ids::FileId i_fileId) override;
	data_types::String GetFileDirectory(const ids::FileId i_fileId) const override;

private:
	data_types::InitOnce<FolderDirectory> m_applicationFolderDirectory;
	data_types::Flag m_initializeFlag;
	std::unordered_map<ids::FileId, FileDirectory> m_mapFileDirectories;
};

} // namespace files
