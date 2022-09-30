#pragma once
#include "Core/GameClock/IGameClock.h"

namespace logic
{

class GameClock: public core::logic::IGameClock
{
public:
	GameClock();
	void UpdateInput(const const core::Duration& dt);
	void PreFixedUpdate(const const core::Duration& dt);
	void FixedUpdate(const const core::Duration& dt);
	void PostFixedUpdate(const const core::Duration& dt);
	void PreUpdate(const const core::Duration& dt);
	void Update(const const core::Duration& dt);
	void PostUpdate(const const core::Duration& dt);
	void PreRender(const const core::Duration& dt);
	void Render(const const core::Duration& dt);
	void PostRender(const const core::Duration& dt);
	void Shutdown();

private:
	bool m_shutDown = false;
};

} // namespace logic