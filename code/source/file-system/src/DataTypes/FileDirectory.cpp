#include "stdafx.h"
#include "FileSystem/DataTypes/FileDirectory.h"

namespace files
{

core::String FileDirectory::ToString() const
{
	return folderDirectory.ToString() + file.ToString();
}

FileDirectory operator+(const FolderDirectory& folder, const File& file)
{
	return FileDirectory
	{
		folder,
		file
	};
}

} // namespace files