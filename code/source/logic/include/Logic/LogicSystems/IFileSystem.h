#pragma once
#include <stdint.h>

namespace ids
{
enum class FileId : uint64_t;
} // namespace ids

namespace core
{
class String;
}

namespace logic
{

class IFileSystem
{
public:
	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual core::String GetTexturesXmlFilePath() const = 0;
	virtual core::String GetSpritesXmlFilePath() const = 0;
	virtual core::String GetAnimationsXmlFilePath() const = 0;
	virtual core::String GetSoundsXmlFilePath() const = 0;
	virtual core::String GetTexturesFolderPath() const = 0;
	virtual core::String GetSoundsFolderPath() const = 0;
	virtual core::String GetAbsolutePath(const core::String i_relativePath) const = 0;
};

} // namespace logic