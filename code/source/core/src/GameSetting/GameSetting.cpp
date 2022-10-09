#pragma once
#include "Core/GameSetting/GameSetting.h"

namespace core
{

GameSetting::GameSetting()
{
}

uint64_t GameSetting::GetMillisecondsPerFrame() const
{
	return 1000 / m_fps;
}

SizeUI64 GameSetting::GetWindowSize() const
{
	return m_windowSize;
}

void GameSetting::SetWindowSize(const SizeUI64& i_windowSize)
{
	m_windowSize = i_windowSize;
	sig_onWindowSizeChange.Emit(i_windowSize);
}

String GameSetting::GetWindowTitle() const
{
	return m_windowTitle;
}

void GameSetting::SetWindowTitle(const String& i_windowTitle)
{
	m_windowTitle = i_windowTitle;
}

uint64_t GameSetting::GetFPS() const
{
	return m_fps;
}

void GameSetting::SetFPS(const uint64_t i_fps)
{
	m_fps = i_fps;
	sig_onChangeFPS.Emit(i_fps);
}

} // namespace core