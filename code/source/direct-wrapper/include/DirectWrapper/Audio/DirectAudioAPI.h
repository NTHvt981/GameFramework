#pragma once
#include "AudioSystem/API/INativeAudioAPI.h"
#include <unordered_map>
#include <memory>
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
	void LoadSound(const core::SoundId i_soundId, const core::String& i_textureFilePath) override;
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