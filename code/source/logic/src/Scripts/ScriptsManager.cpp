#pragma once
#include "Logic/Scripts/ScriptsManager.h"

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
		if (it->Get().scriptState == core::ScriptState::Active)
		{
			it->Get().OnFixedUpdate(dt);
		}
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
		if (it->Get().scriptState == core::ScriptState::Active)
		{
			it->Get().OnRender(dt);
		}
	}
}

void ScriptsManager::OnPostRender(const core::Duration& dt)
{
}

Script::ID ScriptsManager::AddScript(std::unique_ptr<Script> i_script)
{
	m_maxScriptId++;

	i_script->requestAddScriptToManagerCallback = std::bind(
		&ScriptsManager::AddScript, this, std::placeholders::_1
	);

	i_script->id = m_maxScriptId;
	m_scriptsDB[m_maxScriptId] = std::move(i_script);

	m_createdScripts.push(core::Ref(m_scriptsDB[m_maxScriptId].get()));

	return m_maxScriptId;
}

void ScriptsManager::RemoveScript(Script::ID i_scriptID)
{
	m_scriptsDB[i_scriptID]->scriptState = core::ScriptState::Destroyed;
}

void ScriptsManager::ProcessCreatedScripts()
{
	while (!m_createdScripts.empty())
	{
		core::Ref<Script> createdScript = std::move(m_createdScripts.front());

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
		Script::ID id = scriptsToDestroy.front()->Get().id;

		m_activeScripts.erase(scriptsToDestroy.front());

		core::Ref scriptToDestroy = core::Ref(m_scriptsDB[id].get());
		scriptToDestroy->scriptState = core::ScriptState::Destroyed;
		m_destroyedScripts.emplace(scriptToDestroy);

		scriptsToDestroy.pop();
	}
	
	while (!scriptsToPause.empty())
	{
		Script::ID id = scriptsToDestroy.front()->Get().id;

		m_activeScripts.erase(scriptsToPause.front());

		core::Ref<Script> scriptToPause = core::Ref(m_scriptsDB[id].get());
		scriptToPause->scriptState = core::ScriptState::Paused;
		m_pausedScripts.emplace(scriptToPause);

		scriptsToPause.pop();
	}
}

void ScriptsManager::ProcessPausedScripts()
{
	while (!m_pausedScripts.empty())
	{
		core::Ref<Script> pausedScript = std::move(m_pausedScripts.front());

		pausedScript->OnPause();		
		
		switch (pausedScript->scriptState)
		{
		case core::ScriptState::Resumed:
		{
			m_resumedScripts.push(pausedScript);
			break;
		}
		case core::ScriptState::Paused:
			pausedScript->scriptState = core::ScriptState::Inactive;

			m_inactiveScripts.push_back(pausedScript);
		default:
			throw("Invalid state");
			break;
		}

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
		Script::ID id = scriptsToResume.front()->Get().id;

		m_inactiveScripts.erase(scriptsToResume.front());

		core::Ref<Script> scriptToResume = core::Ref(m_scriptsDB[id].get());
		scriptToResume->scriptState = core::ScriptState::Resumed;
		m_resumedScripts.emplace(scriptToResume);

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

		Script::ID id = destroyedScript->id;

		m_destroyedScripts.pop();

		m_scriptsDB[id].release();
		m_scriptsDB.erase(id);
	}
}

} // namespace logic