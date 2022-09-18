#pragma once
#include "IFileSystem.h"

#include <unordered_map>
#include <memory>

namespace core
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
	void ShutDown();
	// Inherited via IFileSystem
	void WriteTextFile(const ids::FileId i_fileId) override;
	void ReadTextFile(const ids::FileId i_fileId) override;
	core::String GetFileDirectory(const ids::FileId i_fileId) const override;

private:
	std::unordered_map<ids::FileId, FileDirectory> m_mapFileDirectories;
};

} // namespace files
