#pragma once
#include <stdint.h>
#include "Core/DataTypes/Ref.h"

namespace core
{
enum class SoundId : uint64_t;
}

namespace audios
{

struct Sound;

namespace database
{

class IAudioDatabaseAPI
{
public:
	virtual core::Ref<Sound> GetSoundRef(const core::SoundId i_soundId) const = 0;
};

} // namespace database

} // namespace audios