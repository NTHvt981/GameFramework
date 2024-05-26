#pragma once
#include "IFileSystem.h"
#include <unordered_map>
#include <memory>

namespace logic
{
class FolderDirectory;
struct FileDirectory;

class FileSystem final : public IFileSystem
{

public:
	FileSystem();
	~FileSystem();
	void Initialize() override;
	void Shutdown() override;
	// Inherited via IFileSystem
	core::String GetAbsolutePath(const core::String i_relativePath) const override;
	core::String GetTexturesXmlFilePath() const override;
	core::String GetSpritesXmlFilePath() const override;
	core::String GetAnimationsXmlFilePath() const override;
	core::String GetSoundsXmlFilePath() const override;
	core::String GetTexturesFolderPath() const override;
	core::String GetSoundsFolderPath() const override;
};

} // namespace logic
