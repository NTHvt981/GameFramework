#pragma once
#include "Core/GameClock/IGameClock.h"

namespace logic
{

class GameClock: public core::logic::IGameClock
{
public:
	GameClock();
	void UpdateInput(const core::Duration& dt);
	void PreFixedUpdate(const core::Duration& dt);
	void FixedUpdate(const core::Duration& dt);
	void PostFixedUpdate(const core::Duration& dt);
	void PreUpdate(const core::Duration& dt);
	void Update(const core::Duration& dt);
	void PostUpdate(const core::Duration& dt);
	void PreRender(const core::Duration& dt);
	void Render(const core::Duration& dt);
	void PostRender(const core::Duration& dt);
	void Shutdown();

private:
	bool m_shutdown = false;
};

} // namespace logic