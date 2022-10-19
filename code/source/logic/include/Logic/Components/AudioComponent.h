#pragma once
#include "IComponent.h"
#include "AudioSystem/DataTypes/SoundSettings.h"
#include "Core/Identifiers/SoundId.h"
#include <memory>

namespace audios
{
class IAudioAPI;
} // namespace audios

namespace logic
{

static constexpr core::ComponentKey sk_audioComponentKey = "AudioComponent";

class AudioComponent final : public IComponent
{
public:
	AudioComponent(std::shared_ptr<audios::IAudioAPI> i_audioAPI);

	// Inherited via Component
	void Register() override {};
	void Deregister() override {};

	bool IsLoop() const;
	void SetLoop(const bool i_value);
	uint64_t GetVolume() const;
	void SetVolume(const uint64_t i_value);
	uint64_t GetFrequency() const;
	void SetFrequency(const uint64_t i_value);
	uint64_t GetPan() const;
	void SetPan(const uint64_t i_value);

	void Play(core::SoundId i_soundId);

private:
	audios::IAudioAPI& m_audioAPI;
	audios::SoundSettings m_settings;
};

} // namespace logic