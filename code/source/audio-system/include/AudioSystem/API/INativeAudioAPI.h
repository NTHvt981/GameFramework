#pragma once
#include "Core/DataTypes/String.h"
#include "AudioSystem/DataTypes/SoundSettings.h"
#include "AudioSystem/DataTypes/Sound.h"

namespace core
{

class INativeAudioAPI
{
public:
	virtual void Initialize() = 0;
	virtual void LoadSound(const Sound& i_sound) = 0;
	virtual void Play(const core::SoundId i_soundId, const SoundSettings& i_settings) = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Shutdown() = 0;
};

} // namespace core
