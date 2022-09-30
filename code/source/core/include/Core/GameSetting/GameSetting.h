#pragma once
#include "Core/DataTypes/Size.h"
#include "Core/DataTypes/String.h"
#include "Core/Signals/Signal.h"

namespace core
{

class GameSetting
{
public:
	GameSetting();

	uint64_t GetMillisecondsPerFrame() const;
	SizeF GetWindowSize() const;
	void SetWindowSize(const SizeF& i_windowSize);
	String GetWindowTitle() const;
	void SetWindowTitle(const String& i_windowTitle);
	uint64_t GetFPS() const;
	void SetFPS(const uint64_t i_fps);

	signals::Signal<SizeF> sig_onWindowSizeChange;
	signals::Signal<uint64_t> sig_onChangeFPS;

private:
	SizeF m_windowSize;
	String m_windowTitle;
	uint64_t m_fps;
};

} // namespace core