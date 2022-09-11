#pragma once
#include "Core/DataTypes/String.h"

namespace files
{

enum class FileId
{
	
};

class IFileSystem
{
public:
	virtual void Initialize() = 0;
	virtual void WriteTextFile(const FileId i_fileId) = 0;
	virtual void ReadTextFile(const FileId i_fileId) = 0;
	virtual data_types::String GetFileDirectory(const FileId i_fileId) const = 0;
};

} // namespace files