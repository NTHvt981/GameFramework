#pragma once
#include "IFileSystem.h"

#include <unordered_map>
#include <memory>

namespace data_types
{
template<typename T>
class InitOnce;
class Flag;
}

namespace files
{
class FolderDirectory;
struct FileDirectory;

class FileSystem final : public IFileSystem
{

public:
	FileSystem();
	~FileSystem();
	void Initialize();
	// Inherited via IFileSystem
	void WriteTextFile(const ids::FileId i_fileId) override;
	void ReadTextFile(const ids::FileId i_fileId) override;
	data_types::String GetFileDirectory(const ids::FileId i_fileId) const override;

private:
	std::unique_ptr<data_types::InitOnce<FolderDirectory>> m_applicationFolderDirectory;
	std::unique_ptr<data_types::Flag> m_initializeFlag;
	std::unordered_map<ids::FileId, FileDirectory> m_mapFileDirectories;
};

} // namespace files
