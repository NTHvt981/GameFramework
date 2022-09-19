#pragma once
#include "Core/GameClock/IGameClock.h"

namespace logic
{

class GameClock: public core::logic::IGameClock
{
public:
	GameClock();
	void UpdateInput(const uint64_t dt);
	void PreFixedUpdate(const uint64_t dt);
	void FixedUpdate(const uint64_t dt);
	void PostFixedUpdate(const uint64_t dt);
	void PreUpdate(const uint64_t dt);
	void Update(const uint64_t dt);
	void PostUpdate(const uint64_t dt);
	void PreRender(const uint64_t dt);
	void Render(const uint64_t dt);
	void PostRender(const uint64_t dt);
	void ShutDown();

private:
	bool m_shutDown = false;
};

} // namespace logic