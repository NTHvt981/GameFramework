#pragma once

namespace audios
{

class INativeAudioAPI
{
public:
	virtual void Initialize() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void ShutDown() = 0;
};

} // namespace audios
