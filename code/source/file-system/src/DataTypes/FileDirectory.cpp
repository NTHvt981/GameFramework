#include "stdafx.h"
#include "FileSystem/DataTypes/FileDirectory.h"

namespace files
{

core::String FileDirectory::ToString() const
{
	return folderDirectory.ToString() + file.name + "." + file.extension;
}

} // namespace files