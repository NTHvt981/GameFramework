#pragma once
#include "Core/Identifiers/SoundId.h"
#include "AudioSystem/DataTypes/SoundSettings.h"

namespace audios
{

class IAudioAPI
{
public:
	virtual void Play(const core::SoundId i_soundId, const SoundSettings& i_settings) = 0;
};

} // namespace audios
