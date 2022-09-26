#pragma once
#include "AudioSystem/AudioSystem.h"

namespace audios
{

AudioSystem::AudioSystem(std::unique_ptr<INativeAudioAPI> i_nativeAudioAPI)
	: m_nativeAudioAPI(std::move(i_nativeAudioAPI))
{
}

void AudioSystem::Initialize()
{
	m_nativeAudioAPI->Initialize();
}

void AudioSystem::Pause()
{
	m_nativeAudioAPI->Pause();
}

void AudioSystem::Resume()
{
	m_nativeAudioAPI->Resume();
}

void AudioSystem::Shutdown()
{
	m_nativeAudioAPI->ShutDown();
}

} // namespace audios