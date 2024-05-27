#pragma once
#include "AudioSystem/API/INativeAudioAPI.h"
#include <unordered_map>
#include <wrl/client.h>
#include <xaudio2.h>

namespace xaudio
{

class XAudio2API final: public core::INativeAudioAPI
{
public:
	XAudio2API();

	// Inherited via INativeAudioAPI
	void Initialize() override;
	void LoadSound(const core::Sound& i_sound) override;
	void Play(const core::SoundId i_soundId, const core::SoundSettings& i_settings) override;
	void Pause() override;
	void Resume() override;
	void Shutdown() override;

private:
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	ComPtr<IXAudio2> m_xAudio2;
	IXAudio2MasteringVoice* m_masterVoice;
	std::unordered_map<core::SoundId, IXAudio2SourceVoice*> m_mapSourceVoices;
};

} // namespace xaudio