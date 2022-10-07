#pragma once
#include "Logic/Managers/ScriptsManager.h"
#include "Logic/Scripts/ScenesScript.h"
#include "Logic/Scripts/WormScript.h" // test

namespace logic
{

ScriptsManager::ScriptsManager(std::shared_ptr<IScriptContext> i_scriptContext)
	: m_scriptContext(i_scriptContext)
{
}

void ScriptsManager::Initialize()
{
	// test
	m_rootScript = std::make_unique<ScenesScript>();
	AddScript(m_rootScript.get());
}

void ScriptsManager::OnPreFixedUpdate(const core::Duration& dt)
{
}

void ScriptsManager::OnFixedUpdate(const core::Duration& dt)
{
	for (auto it = m_activeScripts.begin(); it != m_activeScripts.end(); it++)
	{
		it->Get().OnFixedUpdate(dt);
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
		it->Get().OnUpdate(dt);
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
		it->Get().OnRender(dt);
	}
}

void ScriptsManager::OnPostRender(const core::Duration& dt)
{
}

void ScriptsManager::Shutdown()
{
}

void ScriptsManager::ProcessCreatedScripts()
{
	while (!m_createdScripts.empty())
	{
		core::Ref<Script> createdScript = m_createdScripts.front();

		createdScript->OnCreate(m_scriptContext);
		createdScript->scriptState = core::ScriptState::Active;

		m_activeScripts.push_back(createdScript);
		m_createdScripts.pop();
	}
}

void ScriptsManager::ProcessActiveScripts()
{
	std::queue<std::list<core::Ref<Script>>::iterator> scriptsToDestroy;
	std::queue<std::list<core::Ref<Script>>::iterator> scriptsToPause;

	for (auto it = m_activeScripts.begin(); it != m_activeScripts.end(); it++)
	{
		switch (it->Get().scriptState)
		{
		case core::ScriptState::Destroyed:
		{
			scriptsToDestroy.emplace(it);
			break;
		}
		case core::ScriptState::Paused:
		{
			scriptsToPause.emplace(it);
			break;
		}
		default:
			break;
		}
	}
	
	while (!scriptsToDestroy.empty())
	{
		m_activeScripts.erase(scriptsToDestroy.front(), scriptsToDestroy.front());

		core::Ref<Script> destroyedScript = *scriptsToDestroy.front();
		destroyedScript->scriptState = core::ScriptState::Destroyed;
		m_destroyedScripts.emplace(destroyedScript);
		scriptsToDestroy.pop();
	}
	
	while (!scriptsToPause.empty())
	{
		m_activeScripts.erase(scriptsToPause.front(), scriptsToPause.front());

		core::Ref<Script> pausedScript = *scriptsToPause.front();
		pausedScript->scriptState = core::ScriptState::Paused;
		m_pausedScripts.emplace(pausedScript);
		scriptsToPause.pop();
	}
}

void ScriptsManager::ProcessPausedScripts()
{
	while (!m_pausedScripts.empty())
	{
		core::Ref<Script> pausedScript = m_pausedScripts.front();

		pausedScript->OnPause();
		pausedScript->scriptState = core::ScriptState::Inactive;

		m_inactiveScripts.push_back(pausedScript);
		m_pausedScripts.pop();
	}
}

void ScriptsManager::ProcessInactiveScripts()
{
	std::queue<std::list<core::Ref<Script>>::iterator> scriptsToResume;

	for (auto it = m_inactiveScripts.begin(); it != m_inactiveScripts.end(); it++)
	{
		switch (it->Get().scriptState)
		{
		case core::ScriptState::Resumed:
		{
			scriptsToResume.emplace(it);
			break;
		}
		default:
			break;
		}
	}
	
	while (!scriptsToResume.empty())
	{
		m_inactiveScripts.erase(scriptsToResume.front(), scriptsToResume.front());

		core::Ref<Script> resumedScript = *scriptsToResume.front();
		resumedScript->scriptState = core::ScriptState::Resumed;
		m_resumedScripts.emplace(resumedScript);
		scriptsToResume.pop();
	}
}

void ScriptsManager::ProcessResumedScripts()
{
	while (!m_resumedScripts.empty())
	{
		core::Ref<Script> resumedScript = m_resumedScripts.front();

		resumedScript->OnResume();
		resumedScript->scriptState = core::ScriptState::Active;

		m_activeScripts.push_back(resumedScript);
		m_resumedScripts.pop();
	}
}

void ScriptsManager::ProcessDestroyedScripts()
{
	while (!m_destroyedScripts.empty())
	{
		core::Ref<Script> destroyedScript = m_destroyedScripts.front();

		destroyedScript->OnDestroy();
		destroyedScript->scriptState = core::ScriptState::ConfirmedDestroyed;

		m_destroyedScripts.pop();
	}
}

void ScriptsManager::AddScript(core::Ref<Script> i_script)
{
	m_createdScripts.emplace(i_script);
	i_script->requestAddScriptToManagerCallback = std::bind(
		&ScriptsManager::AddScript, this, std::placeholders::_1
	);
}

} // namespace logic