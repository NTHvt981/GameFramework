#include "IntroScript.h"
#include "Logic/ComponentKeys/WormKeys.h"
#include "Core/GameClock/IGameClock.h"
#include "Logic/Entities/IEntitiesFactory.h"
#include "Logic/Entities/EntitiesManager.h"
#include "Logic/Entities/Entity.h"
#include "Logic/Components/TransformCompositionComponent.h"
#include "Logic/Components/KinematicBodyComponent.h"
#include "Logic/Components/AnimationComponent.h"
#include "Core/Signals/Connection.h"

namespace logic
{

void IntroScript::OnCreate(core::Ref<IScriptContext> i_scriptContext)
{	
	m_introEntity = i_scriptContext->GetEntitiesFactory()->MakeIntroEntity();
	i_scriptContext->GetEntitiesManager()->AddEntity(m_introEntity);
	m_introEntity->Register();

	m_animationComponent = m_introEntity->GetComponent<AnimationComponent>(sk_animationComponentKey);
	m_cameraComponent = m_introEntity->GetComponent<CameraComponent>(sk_cameraComponentKey);
	m_audioComponent = m_introEntity->GetComponent<AudioComponent>(sk_audioComponentKey);

	m_animationComponent->SetSpeed(1.0f);
	m_animationComponent->SetLoop(false);

	m_animationFinishedCon = m_animationComponent->sig_onAnimationFinished.Connect(
		std::bind(&IntroScript::OnAnimationFinished, this)
	);
}

void IntroScript::OnDestroy()
{
	m_introEntity->Deregister();
	sig_onIntroFinished.Emit();
}

void IntroScript::OnFixedUpdate(const core::Duration& dt)
{

}

IntroScript::~IntroScript()
{
}

void IntroScript::OnAnimationFinished()
{
	scriptState = core::ScriptState::Destroyed;
	m_animationFinishedCon.Disconnect();
}

} // namespace logic