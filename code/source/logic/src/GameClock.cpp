#include "..\include\Logic\GameClock.h"

namespace logic
{

GameClock::GameClock()
{
}

void GameClock::UpdateInput(const uint64_t dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onUpdateInput.Emit(dt);
}

void GameClock::PreFixedUpdate(const uint64_t dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onPreFixedUpdate.Emit(dt);
}

void GameClock::FixedUpdate(const uint64_t dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onFixedUpdate.Emit(dt);
}

void GameClock::PostFixedUpdate(const uint64_t dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onPostFixedUpdate.Emit(dt);
}

void GameClock::PreUpdate(const uint64_t dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onPreUpdate.Emit(dt);
}

void GameClock::Update(const uint64_t dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onUpdate.Emit(dt);
}

void GameClock::PostUpdate(const uint64_t dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onPostUpdate.Emit(dt);
}

void GameClock::PreRender(const uint64_t dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onPreRender.Emit(dt);
}

void GameClock::Render(const uint64_t dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onRender.Emit(dt);
}

void GameClock::PostRender(const uint64_t dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onPostRender.Emit(dt);
}

void GameClock::Shutdown()
{
	m_shutDown = true;
}

} // namespace logic
