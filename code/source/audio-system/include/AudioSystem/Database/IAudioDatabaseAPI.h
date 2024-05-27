#pragma once
#include <stdint.h>
#include "Core/DataTypes/Ref.h"

namespace core
{
enum class SoundId : uint64_t;
struct Sound;
}

namespace audios
{

namespace database
{

class IAudioDatabaseAPI
{
public:
	virtual core::Ref<core::Sound> GetSoundRef(const core::SoundId i_soundId) const = 0;
};

} // namespace database

} // namespace audios