#pragma once
#include "Core/Identifiers/SoundId.h"
#include "Core/DataTypes/String.h"

namespace core
{

struct Sound
{
	core::SoundId id;
	core::String filePath;
	bool loop;
};

} // namespace core