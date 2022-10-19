#pragma once
#include <stdint.h>

namespace audios
{

struct SoundSettings
{
	bool loop = false;
	uint16_t volume = 0;
	uint16_t frequency = 0;
	uint16_t pan = 0;
};

} // namespace audios