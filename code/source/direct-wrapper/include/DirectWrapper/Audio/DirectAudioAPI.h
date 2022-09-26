#pragma once
#include "AudioSystem/API/INativeAudioAPI.h"
#include <windows.h>
#include <dsound.h>

namespace audios
{

class DirectAudioAPI final: public INativeAudioAPI
{
public:
	DirectAudioAPI(const HWND i_hwnd);

	// Inherited via INativeAudioAPI
	void Initialize() override;
	void Pause() override;
	void Resume() override;
	void ShutDown() override;

private:
	const HWND m_hwnd;
	LPDIRECTSOUND8 m_directSound = nullptr;
	LPDIRECTSOUNDBUFFER m_directSoundBuffer = NULL;
};

} // namespace audios