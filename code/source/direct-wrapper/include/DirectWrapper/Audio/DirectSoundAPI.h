#pragma once
#include "AudioSystem/API/INativeAudioAPI.h"
#include <unordered_map>
#include <memory>
#include <windows.h>
#include <dsound.h>

namespace audios
{

class DirectSoundAPI final: public INativeAudioAPI
{
public:
	DirectSoundAPI(const HWND i_hwnd);

	// Inherited via INativeAudioAPI
	void Initialize() override;
	void LoadSound(const Sound& i_sound) override;
	void Play(const core::SoundId i_soundId, const SoundSettings& i_settings) override;
	void Pause() override;
	void Resume() override;
	void Shutdown() override;

private:
	const HWND m_hwnd;
	LPDIRECTSOUND8 m_directSound = nullptr;
	LPDIRECTSOUNDBUFFER m_primarySoundBuffer;
	std::unordered_map<core::SoundId, LPDIRECTSOUNDBUFFER> m_mapSoundBuffers;
};

} // namespace audios