#include "..\include\Logic\GameClock.h"

namespace logic
{

GameClock::GameClock()
{
}

void GameClock::UpdateInput(const core::Duration& dt)
{
	if (m_shutdown)
	{
		return;
	}

	sig_onUpdateInput.Emit(dt);
}

void GameClock::PreFixedUpdate(const core::Duration& dt)
{
	if (m_shutdown)
	{
		return;
	}

	sig_onPreFixedUpdate.Emit(dt);
}

void GameClock::FixedUpdate(const core::Duration& dt)
{
	if (m_shutdown)
	{
		return;
	}

	sig_onFixedUpdate.Emit(dt);
}

void GameClock::PostFixedUpdate(const core::Duration& dt)
{
	if (m_shutdown)
	{
		return;
	}

	sig_onPostFixedUpdate.Emit(dt);
}

void GameClock::PreUpdate(const core::Duration& dt)
{
	if (m_shutdown)
	{
		return;
	}

	sig_onPreUpdate.Emit(dt);
}

void GameClock::Update(const core::Duration& dt)
{
	if (m_shutdown)
	{
		return;
	}

	sig_onUpdate.Emit(dt);
}

void GameClock::PostUpdate(const core::Duration& dt)
{
	if (m_shutdown)
	{
		return;
	}

	sig_onPostUpdate.Emit(dt);
}

void GameClock::PreRender(const core::Duration& dt)
{
	if (m_shutdown)
	{
		return;
	}

	sig_onPreRender.Emit(dt);
}

void GameClock::Render(const core::Duration& dt)
{
	if (m_shutdown)
	{
		return;
	}

	sig_onRender.Emit(dt);
}

void GameClock::PostRender(const core::Duration& dt)
{
	if (m_shutdown)
	{
		return;
	}

	sig_onPostRender.Emit(dt);
}

void GameClock::Shutdown()
{
	m_shutdown = true;
}

} // namespace logic
