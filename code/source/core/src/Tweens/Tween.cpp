#include "Core/Tweens/Tween.h"
#include <math.h>

namespace core
{

Tween::Tween(std::shared_ptr<logic::IGameClock> i_gameClock, const float i_fromValue, const float i_toValue)
	: m_gameClock(*i_gameClock.get())
	, fromValue(i_fromValue)
	, toValue(i_toValue)
	, currentValue(i_fromValue)
{
}

Tween::~Tween()
{
}

void Tween::Start()
{
	Reset();
	m_onPreUpdateCon = m_gameClock.sig_onPreUpdate.Connect(
		std::bind(&Tween::OnPreUpdate, this, std::placeholders::_1)
	);
}

void Tween::Reset()
{
	currentValue = fromValue;
}

void Tween::Pause()
{
	m_onPreUpdateCon.Disconnect();
}

void Tween::Resume()
{
	m_onPreUpdateCon = m_gameClock.sig_onPreUpdate.Connect(
		std::bind(&Tween::OnPreUpdate, this, std::placeholders::_1)
	);
}

void Tween::OnPreUpdate(const core::Duration& i_duration)
{
	_OnPreUpdate(i_duration);
}

} // namespace core