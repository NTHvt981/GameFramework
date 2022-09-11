#include "FileSystem/DataTypes/FileDirectory.h"

namespace files
{

data_types::String FileDirectory::ToString()
{
	return folderDirectory.ToString() + file.name + "." + file.extension;
}

} // namespace files