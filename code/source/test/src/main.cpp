#include "FileSystem/FileSystem.h"
#include <memory>

int main()
{
	std::shared_ptr<files::IFileSystem> fileSystem = std::make_shared<files::FileSystem>();
	fileSystem->Initialize();
	const data_types::String path = fileSystem->GetFileDirectory(ids::FileId::BossTexture);
	return 0;
}