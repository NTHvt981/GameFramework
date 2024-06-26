#pragma once
#include "IAudioSystem.h"
#include "Database/IAudioDatabaseAPI.h"
#include <memory>

namespace core
{
class INativeAudioAPI;
}

namespace audios
{

class AudioSystem final: public IAudioSystem
{
public:
	AudioSystem(
		std::unique_ptr<core::INativeAudioAPI> i_nativeAudioAPI,
		std::shared_ptr<const database::IAudioDatabaseAPI> i_databaseAPI
	);

	// Inherited via IAudioSystem
	void Initialize() override;
	void LoadSounds() override;
	void Play(const core::SoundId i_soundId, const core::SoundSettings& i_settings) override;
	void Pause() override;
	void Resume() override;
	void Shutdown() override;

private:
	std::unique_ptr<core::INativeAudioAPI> m_nativeAudioAPI;
	std::shared_ptr<const database::IAudioDatabaseAPI> m_databaseAPI;
};

} // namespace audios