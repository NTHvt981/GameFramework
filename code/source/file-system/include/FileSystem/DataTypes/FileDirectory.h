#pragma once
#include "File.h"
#include "FolderDirectory.h"

namespace files
{

struct FileDirectory
{
	FolderDirectory folderDirectory{};
	File file;
	data_types::String ToString();
};

} // namespace files