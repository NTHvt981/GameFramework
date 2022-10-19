#include "Logic/Components/AudioComponent.h"
#include "AudioSystem/API/IAudioAPI.h"

namespace logic
{

AudioComponent::AudioComponent(std::shared_ptr<audios::IAudioAPI> i_audioAPI)
	: m_audioAPI(*i_audioAPI.get())
{
}

bool AudioComponent::IsLoop() const
{
	return m_settings.loop;
}

void AudioComponent::SetLoop(const bool i_value)
{
	m_settings.loop = i_value;
}

uint64_t AudioComponent::GetVolume() const
{
	return m_settings.volume;
}

void AudioComponent::SetVolume(const uint64_t i_value)
{
	m_settings.volume = i_value;
}

uint64_t AudioComponent::GetFrequency() const
{
	return m_settings.frequency;
}

void AudioComponent::SetFrequency(const uint64_t i_value)
{
	m_settings.frequency = i_value;
}

uint64_t AudioComponent::GetPan() const
{
	return m_settings.pan;
}

void AudioComponent::SetPan(const uint64_t i_value)
{
	m_settings.pan = i_value;
}

void AudioComponent::Play(core::SoundId i_soundId)
{
	m_audioAPI.Play(i_soundId, m_settings);
}

} // namespace logic