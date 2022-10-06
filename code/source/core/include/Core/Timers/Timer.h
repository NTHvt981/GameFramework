#pragma once
#include "Core/DataTypes/Duration.h"
#include "Core/GameClock/IGameClock.h"
#include "Core/Signals/Signal.h"
#include <memory>

namespace core
{

class Timer
{
public:
	Timer(
		std::shared_ptr<logic::IGameClock> i_gameClock,
		const core::Duration i_duration = core::Duration(0)
	);
	~Timer();
	void Start();
	void Reset();
	void Pause();
	void Resume();
	void SetDuration(const core::Duration& i_duration);
	core::Duration GetDuration() const;
	bool IsFinished() const;
	
	signals::Signal<> sig_onFinished;
	float speed = 1;
private:
	void OnPreUpdate(const core::Duration& i_duration);
	bool m_isFinished = false;
	core::Duration m_duration;
	core::Duration m_currentDuration;
	logic::IGameClock& m_gameClock;
	signals::Connection<const core::Duration&> m_onPreUpdateCon;
};

} // namespace core