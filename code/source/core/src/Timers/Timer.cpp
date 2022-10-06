#include "Core/Timers/Timer.h"
#include <math.h>

namespace core
{

Timer::Timer(std::shared_ptr<logic::IGameClock> i_gameClock, const core::Duration i_duration)
	: m_gameClock(*i_gameClock.get())
	, m_duration(i_duration)
	, m_currentDuration(0)
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
	Reset();
	m_onPreUpdateCon = m_gameClock.sig_onPreUpdate.Connect(
		std::bind(&Timer::OnPreUpdate, this, std::placeholders::_1)
	);
}

void Timer::Reset()
{
	m_currentDuration = core::Duration(0);
	m_isFinished = false;
}

void Timer::Pause()
{
	m_onPreUpdateCon.Disconnect();
}

void Timer::Resume()
{
	m_onPreUpdateCon = m_gameClock.sig_onPreUpdate.Connect(
		std::bind(&Timer::OnPreUpdate, this, std::placeholders::_1)
	);
}

void Timer::SetDuration(const core::Duration& i_duration)
{
	m_duration = i_duration;
}

core::Duration Timer::GetDuration() const
{
	return m_duration;
}

bool Timer::IsFinished() const
{
	return m_isFinished;
}

void Timer::OnPreUpdate(const core::Duration& i_duration)
{
	m_currentDuration = m_currentDuration + i_duration * speed;
	if (m_currentDuration > m_duration)
	{
		m_isFinished = true;
		m_currentDuration = m_duration;
		sig_onFinished.Emit();
		m_onPreUpdateCon.Disconnect();
	}
}

} // namespace core