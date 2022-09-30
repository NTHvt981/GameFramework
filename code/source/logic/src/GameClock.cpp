#include "..\include\Logic\GameClock.h"

namespace logic
{

GameClock::GameClock()
{
}

void GameClock::UpdateInput(const const core::Duration& dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onUpdateInput.Emit(dt);
}

void GameClock::PreFixedUpdate(const const core::Duration& dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onPreFixedUpdate.Emit(dt);
}

void GameClock::FixedUpdate(const const core::Duration& dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onFixedUpdate.Emit(dt);
}

void GameClock::PostFixedUpdate(const const core::Duration& dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onPostFixedUpdate.Emit(dt);
}

void GameClock::PreUpdate(const const core::Duration& dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onPreUpdate.Emit(dt);
}

void GameClock::Update(const const core::Duration& dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onUpdate.Emit(dt);
}

void GameClock::PostUpdate(const const core::Duration& dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onPostUpdate.Emit(dt);
}

void GameClock::PreRender(const const core::Duration& dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onPreRender.Emit(dt);
}

void GameClock::Render(const const core::Duration& dt)
{
	if (m_shutDown)
	{
		return;
	}

	sig_onRender.Emit(dt);
}

void GameClock::PostRender(const const core::Duration& dt)
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
