#include "Core/DataTypes/FileDirectory.h"

namespace core
{

String FileDirectory::ToString() const
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

} // namespace core