#pragma once
#include "API/IAudioAPI.h"

namespace audios
{

class IAudioSystem: public IAudioAPI
{
public:
	virtual void Initialize() = 0;
	virtual void LoadSounds() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Shutdown() = 0;
};

} // namespace audios