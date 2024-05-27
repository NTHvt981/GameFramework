#pragma once
#include "AudioSystem/AudioSystem.h"
#include "AudioSystem/API/INativeAudioAPI.h"
#include "AudioSystem/DataTypes/Sound.h"
#include "Core/Identifiers/SoundId.h"

namespace audios
{

////////////////////////////////////////////////////////////////////////////////

AudioSystem::AudioSystem(
	std::unique_ptr<core::INativeAudioAPI> i_nativeAudioAPI,
	std::shared_ptr<const database::IAudioDatabaseAPI> i_databaseAPI)
	: m_nativeAudioAPI(std::move(i_nativeAudioAPI))
	, m_databaseAPI(i_databaseAPI)
{
}

////////////////////////////////////////////////////////////////////////////////

void AudioSystem::Initialize()
{
	m_nativeAudioAPI->Initialize();
}

////////////////////////////////////////////////////////////////////////////////

void AudioSystem::LoadSounds()
{
	for (const core::SoundId id : core::SoundIdIterators())
	{
		core::Ref<core::Sound> sound = m_databaseAPI->GetSoundRef(id);
		m_nativeAudioAPI->LoadSound(sound.Get());
	}
}

////////////////////////////////////////////////////////////////////////////////

void AudioSystem::Play(const core::SoundId i_soundId, const core::SoundSettings& i_settings)
{
	m_nativeAudioAPI->Play(i_soundId, i_settings);
}

////////////////////////////////////////////////////////////////////////////////

void AudioSystem::Pause()
{
	m_nativeAudioAPI->Pause();
}

////////////////////////////////////////////////////////////////////////////////

void AudioSystem::Resume()
{
	m_nativeAudioAPI->Resume();
}

////////////////////////////////////////////////////////////////////////////////

void AudioSystem::Shutdown()
{
	m_nativeAudioAPI->Shutdown();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace audios