#pragma once
#include "IFileSystem.h"

#include <unordered_map>
#include <memory>

namespace data_types
{
template<typename T>
class InitOnce;
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
	std::unordered_map<ids::FileId, FileDirectory> m_mapFileDirectories;
};

} // namespace files
