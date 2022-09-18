#pragma once
#include <stdint.h>

namespace ids
{
enum class FileId : uint64_t;
} // namespace ids

namespace core
{
class String;
}

namespace files
{

class IFileSystem
{
public:
	virtual void WriteTextFile(const ids::FileId i_fileId) = 0;
	virtual void ReadTextFile(const ids::FileId i_fileId) = 0;
	virtual core::String GetFileDirectory(const ids::FileId i_fileId) const = 0;
};

} // namespace files