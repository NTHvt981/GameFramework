#pragma once
#include "Core/Identifiers/SoundId.h"
#include "Core/DataTypes/String.h"

namespace audios
{

struct Sound
{
	core::SoundId id;
	core::String filePath;
};

} // namespace audios