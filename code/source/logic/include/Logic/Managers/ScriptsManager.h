#pragma once
#include "Logic/Scripts/Script.h"
#include <list>
#include <queue>
#include <memory>

namespace logic
{

class Script;

class ScriptsManager
{
public:

private:
	std::queue<std::unique_ptr<Script>> m_onCreatedScripts;
	std::list<std::unique_ptr<Script>> m_onGoingScripts;
	std::queue<std::unique_ptr<Script>> m_onPausedScripts;
	std::queue<std::unique_ptr<Script>> m_onResumedScripts;
	std::queue<std::unique_ptr<Script>> m_onDestroyedScripts;
};

} // namespace logic