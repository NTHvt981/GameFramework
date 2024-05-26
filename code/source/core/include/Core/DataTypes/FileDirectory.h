#pragma once
#include "File.h"
#include "FolderDirectory.h"

namespace core
{

struct FileDirectory
{
	FolderDirectory folderDirectory;
	File file;
	String ToString() const;
};

FileDirectory operator+(const FolderDirectory& folder, const File& file);

} // namespace core