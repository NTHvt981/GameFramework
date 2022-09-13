#include "FileSystem/FileSystem.h"
#include "Core/DataTypes/String.h"
#include "Core/Identifiers/FileId.h"
#include <stdint.h>
#include <memory>

int main()
{
	std::shared_ptr<files::FileSystem> fileSystem = std::make_shared<files::FileSystem>();
	fileSystem->Initialize();
	const data_types::String path = fileSystem->GetFileDirectory(ids::FileId::BossTexture);
	return 0;
}