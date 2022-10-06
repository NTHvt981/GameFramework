#pragma once
#include "Logic/Scripts/Script.h"
#include "Logic/Scripts/IScriptContext.h"
#include "Core/DataTypes/Ref.h"
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

	void Initialize();
	void OnPreFixedUpdate(const core::Duration& dt);
	void OnFixedUpdate(const core::Duration& dt);
	void OnPostFixedUpdate(const core::Duration& dt);
	void OnPreUpdate(const core::Duration& dt);
	void OnUpdate(const core::Duration& dt);
	void OnPostUpdate(const core::Duration& dt);
	void OnPreRender(const core::Duration& dt);
	void OnRender(const core::Duration& dt);
	void OnPostRender(const core::Duration& dt);
	void Shutdown();

private:
	void ProcessCreatedScripts();
	void ProcessActiveScripts();
	void ProcessPausedScripts();
	void ProcessInactiveScripts();
	void ProcessResumedScripts();
	void ProcessDestroyedScripts();
	void RequestCreateScript(core::Ref<Script> i_script);

	std::queue<core::Ref<Script>> m_createdScripts;
	std::list<core::Ref<Script>> m_activeScripts;
	std::list<core::Ref<Script>> m_inactiveScripts;
	std::queue<core::Ref<Script>> m_pausedScripts;
	std::queue<core::Ref<Script>> m_resumedScripts;
	std::queue<core::Ref<Script>> m_destroyedScripts;

	std::shared_ptr<IScriptContext> m_scriptContext;
	std::unique_ptr<Script> m_rootScript;
};

} // namespace logic