#pragma once
#include "Core/Identifiers/SoundId.h"
#include "Core/DataTypes/String.h"

namespace audios
{

class INativeAudioAPI
{
public:
	virtual void Initialize() = 0;
	virtual void LoadSound(const core::SoundId i_soundId, const core::String& i_textureFilePath) = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Shutdown() = 0;
};

} // namespace audios
