#include "Logic/Scripts/WormScript.h"
#include "Logic/ComponentKeys/WormKeys.h"
#include "Core/GameClock/IGameClock.h"
#include "Logic/Factories/IEntitiesFactory.h"
#include "Logic/Managers/EntitiesManager.h"
#include "Logic/Entities/Entity.h"
#include "Logic/Components/TransformCompositionComponent.h"
#include "Logic/Components/KinematicBodyComponent.h"
#include "Logic/Components/AnimationComponent.h"
#include "Core/Signals/Connection.h"

namespace logic
{

void WormScript::OnCreate(std::shared_ptr<IScriptContext> i_scriptContext)
{
	auto gameClock = i_scriptContext->GetGameClock();
	m_onFixedUpdateCon = gameClock->sig_onFixedUpdate.Connect(
		std::bind(&WormScript::OnFixedUpdate, this, std::placeholders::_1)
	);
	m_onUpdateCon = gameClock->sig_onUpdate.Connect(
		std::bind(&WormScript::OnUpdate, this, std::placeholders::_1)
	);
	
	m_wormEntity = i_scriptContext->GetEntitiesFactory()->MakeWormEntity();
	i_scriptContext->GetEntitiesManager()->AddEntity(m_wormEntity);
	m_wormEntity->Register();

	m_kinematicComponent = m_wormEntity->GetComponent<KinematicBodyComponent>(sk_kinematicBodyComponentKey);
	m_transformComponent = m_wormEntity->GetComponent<TransformCompositionComponent>(sk_transformCompositionComponentKey);
	m_animationComponent = m_wormEntity->GetComponent<AnimationComponent>(sk_animationComponentKey);

	m_moveCon = m_kinematicComponent->sig_onMove.Connect(
		std::bind(&TransformCompositionComponent::SetPosition, m_transformComponent.get(), std::placeholders::_1)
	);

	m_transformComponent->SetPosition(core::Vector2F{ 50, 100 });
}

void WormScript::OnDestroy()
{
	m_wormEntity->Deregister();
	m_onFixedUpdateCon.Disconnect();
	m_onUpdateCon.Disconnect();
}

void WormScript::OnFixedUpdate(const core::Duration& dt)
{
	m_kinematicComponent->Move(core::Vector2F{ 20 * dt.ToSecond(), 0 });
}

void WormScript::OnUpdate(const core::Duration& dt)
{
}

} // namespace logic