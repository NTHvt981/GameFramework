#pragma once
#include "Logic/Managers/ScriptsManager.h"

namespace logic
{

ScriptsManager::ScriptsManager(std::shared_ptr<IScriptContext> i_scriptContext)
	: m_scriptContext(i_scriptContext)
{
}

void ScriptsManager::OnPreFixedUpdate(const core::Duration& dt)
{
}

void ScriptsManager::OnFixedUpdate(const core::Duration& dt)
{
	for (auto it = m_activeScripts.begin(); it != m_activeScripts.end(); it++)
	{
		(*it)->OnFixedUpdate(dt);
	}
}

void ScriptsManager::OnPostFixedUpdate(const core::Duration& dt)
{
}

void ScriptsManager::OnPreUpdate(const core::Duration& dt)
{
	ProcessInactiveScripts();
	ProcessResumedScripts();
	ProcessCreatedScripts();
}

void ScriptsManager::OnUpdate(const core::Duration& dt)
{
	for (auto it = m_activeScripts.begin(); it != m_activeScripts.end(); it++)
	{
		(*it)->OnUpdate(dt);
	}
}

void ScriptsManager::OnPostUpdate(const core::Duration& dt)
{
	ProcessActiveScripts();
	ProcessPausedScripts();
	ProcessDestroyedScripts();
}

void ScriptsManager::OnPreRender(const core::Duration& dt)
{
}

void ScriptsManager::OnRender(const core::Duration& dt)
{
	for (auto it = m_activeScripts.begin(); it != m_activeScripts.end(); it++)
	{
		(*it)->OnRender(dt);
	}
}

void ScriptsManager::OnPostRender(const core::Duration& dt)
{
}

void ScriptsManager::ProcessCreatedScripts()
{
	while (!m_createdScripts.empty())
	{
		std::unique_ptr<Script> createdScript = std::move(m_createdScripts.front());

		createdScript->OnCreate(m_scriptContext);
		createdScript->scriptState = core::ScriptState::Active;

		m_activeScripts.push_back(std::move(createdScript));
		m_createdScripts.pop();
	}
}

void ScriptsManager::ProcessActiveScripts()
{
	std::queue<std::list<std::unique_ptr<Script>>::iterator> scriptsToDestroy;
	std::queue<std::list<std::unique_ptr<Script>>::iterator> scriptsToPause;

	for (auto it = m_activeScripts.begin(); it != m_activeScripts.end(); it++)
	{
		switch ((*it)->scriptState)
		{
		case core::ScriptState::Destroyed:
		{
			scriptsToDestroy.push(std::move(it));
			break;
		}
		case core::ScriptState::Paused:
		{
			scriptsToPause.push(std::move(it));
			break;
		}
		default:
			break;
		}
	}
	
	while (!scriptsToDestroy.empty())
	{
		m_activeScripts.erase(scriptsToDestroy.front(), scriptsToDestroy.front());

		std::unique_ptr<Script> destroyedScript = std::move(*scriptsToDestroy.front());
		destroyedScript->scriptState = core::ScriptState::Destroyed;
		m_destroyedScripts.push(std::move(destroyedScript));
		scriptsToDestroy.pop();
	}
	
	while (!scriptsToPause.empty())
	{
		m_activeScripts.erase(scriptsToPause.front(), scriptsToPause.front());

		std::unique_ptr<Script> pausedScript = std::move(*scriptsToPause.front());
		pausedScript->scriptState = core::ScriptState::Paused;
		m_pausedScripts.push(std::move(pausedScript));
		scriptsToPause.pop();
	}
}

void ScriptsManager::ProcessPausedScripts()
{
	while (!m_pausedScripts.empty())
	{
		std::unique_ptr<Script> pausedScript = std::move(m_pausedScripts.front());

		pausedScript->OnPause();
		pausedScript->scriptState = core::ScriptState::Inactive;

		m_inactiveScripts.push_back(std::move(pausedScript));
		m_pausedScripts.pop();
	}
}

void ScriptsManager::ProcessInactiveScripts()
{
	std::queue<std::list<std::unique_ptr<Script>>::iterator> scriptsToResume;

	for (auto it = m_inactiveScripts.begin(); it != m_activeScripts.end(); it++)
	{
		switch ((*it)->scriptState)
		{
		case core::ScriptState::Resumed:
		{
			scriptsToResume.push(std::move(it));
			break;
		}
		default:
			break;
		}
	}
	
	while (!scriptsToResume.empty())
	{
		m_inactiveScripts.erase(scriptsToResume.front(), scriptsToResume.front());

		std::unique_ptr<Script> resumedScript = std::move(*scriptsToResume.front());
		resumedScript->scriptState = core::ScriptState::Resumed;
		m_resumedScripts.push(std::move(resumedScript));
		scriptsToResume.pop();
	}
}

void ScriptsManager::ProcessResumedScripts()
{
	while (!m_resumedScripts.empty())
	{
		std::unique_ptr<Script> resumedScript = std::move(m_resumedScripts.front());

		resumedScript->OnResume();
		resumedScript->scriptState = core::ScriptState::Active;

		m_activeScripts.push_back(std::move(resumedScript));
		m_resumedScripts.pop();
	}
}

void ScriptsManager::ProcessDestroyedScripts()
{
	while (!m_destroyedScripts.empty())
	{
		std::unique_ptr<Script> destroyedScript = std::move(m_destroyedScripts.front());

		destroyedScript->OnDestroy();

		m_destroyedScripts.pop();
	}
}

} // namespace logic