#pragma once
#include "Core/DataTypes/String.h"
#include "Core/Identifiers/FileId.h"

namespace files
{

class IFileSystem
{
public:
	virtual void Initialize() = 0;
	virtual void WriteTextFile(const ids::FileId i_fileId) = 0;
	virtual void ReadTextFile(const ids::FileId i_fileId) = 0;
	virtual data_types::String GetFileDirectory(const ids::FileId i_fileId) const = 0;
};

} // namespace files