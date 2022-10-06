#pragma once
#include "Core/DataTypes/Duration.h"
#include "Core/GameClock/IGameClock.h"
#include "Core/Signals/Signal.h"
#include <memory>

namespace core
{

class Tween
{
public:
	Tween(
		std::shared_ptr<logic::IGameClock> i_gameClock,
		const float i_fromValue,
		const float i_toValue
	);
	~Tween();
	void Start();
	void Reset();
	void Pause();
	void Resume();

	float currentValue = 0;
	float fromValue = 0;
	float toValue = 0;
private:
	void OnPreUpdate(const core::Duration& i_duration);

	logic::IGameClock& m_gameClock;
	signals::Connection<const core::Duration&> m_onPreUpdateCon;

private:
	virtual void _OnPreUpdate(const core::Duration& i_duration) = 0;
};

} // namespace core