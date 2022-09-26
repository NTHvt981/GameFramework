#include "Logic/Scripts/WormScript.h"

namespace logic
{

void WormScript::Initialize(std::shared_ptr<IScriptContext> i_scriptContext)
{
	auto gameClock = i_scriptContext->GetGameClock();
	m_onFixedUpdateCon = gameClock->sig_onFixedUpdate.Connect(
		std::bind(&WormScript::OnFixedUpdate, this, std::placeholders::_1)
	);
	m_onUpdateCon = gameClock->sig_onUpdate.Connect(
		std::bind(&WormScript::OnUpdate, this, std::placeholders::_1)
	);

	m_wormEntity = i_scriptContext->GetEntityFactory()->MakeWormEntity();
	m_wormEntity->root->Register();
}

void WormScript::Shutdown()
{
	m_onFixedUpdateCon.Disconnect();
	m_onUpdateCon.Disconnect();
}

void WormScript::OnFixedUpdate(uint64_t dt)
{
}

void WormScript::OnUpdate(uint64_t dt)
{
}

} // namespace logic