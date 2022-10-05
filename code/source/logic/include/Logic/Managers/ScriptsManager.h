#pragma once
#include "Logic/Scripts/Script.h"
#include "Logic/Scripts/IScriptContext.h"
#include <list>
#include <queue>
#include <memory>

namespace logic
{

class Script;

class ScriptsManager
{
public:
	ScriptsManager(std::shared_ptr<IScriptContext> i_scriptContext);

	void OnPreFixedUpdate(const core::Duration& dt);
	void OnFixedUpdate(const core::Duration& dt);
	void OnPostFixedUpdate(const core::Duration& dt);
	void OnPreUpdate(const core::Duration& dt);
	void OnUpdate(const core::Duration& dt);
	void OnPostUpdate(const core::Duration& dt);
	void OnPreRender(const core::Duration& dt);
	void OnRender(const core::Duration& dt);
	void OnPostRender(const core::Duration& dt);

private:
	void ProcessCreatedScripts();
	void ProcessActiveScripts();
	void ProcessPausedScripts();
	void ProcessInactiveScripts();
	void ProcessResumedScripts();
	void ProcessDestroyedScripts();

	std::queue<std::unique_ptr<Script>> m_createdScripts;
	std::list<std::unique_ptr<Script>> m_activeScripts;
	std::list<std::unique_ptr<Script>> m_inactiveScripts;
	std::queue<std::unique_ptr<Script>> m_pausedScripts;
	std::queue<std::unique_ptr<Script>> m_resumedScripts;
	std::queue<std::unique_ptr<Script>> m_destroyedScripts;

	std::shared_ptr<IScriptContext> m_scriptContext;
};

} // namespace logic