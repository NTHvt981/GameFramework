#pragma once
#include "File.h"
#include "FolderDirectory.h"

namespace files
{

struct FileDirectory
{
	FolderDirectory folderDirectory;
	File file;
	core::String ToString() const;
};

FileDirectory operator+(const FolderDirectory& folder, const File& file);

} // namespace files