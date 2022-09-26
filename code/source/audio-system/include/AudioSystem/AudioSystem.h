#pragma once
#include "IAudioSystem.h"
#include "API/INativeAudioAPI.h"
#include <memory>

namespace audios
{

class AudioSystem final: public IAudioSystem
{
public:
	AudioSystem(std::unique_ptr<INativeAudioAPI> i_nativeAudioAPI);

	// Inherited via IAudioSystem
	void Initialize() override;
	void Pause() override;
	void Resume() override;
	void Shutdown() override;

private:
	std::unique_ptr<INativeAudioAPI> m_nativeAudioAPI;
};

} // namespace audios