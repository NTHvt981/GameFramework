#pragma once
#include "Logic/Scripts/IntroSceneScript.h"
#include "Logic/Scripts/SideScrollSceneScript.h"
#include "Logic/Scripts/IScriptContext.h"
#include "Logic/Factories/IEntitiesFactory.h"
#include "Logic/Managers/EntitiesManager.h"
#include "Logic/Components/AnimationComponent.h"
#include "Logic/Components/AudioComponent.h"
#include "Logic/Components/CameraComponent.h"
#include "Core/Helpers/SizeHelper.h"

namespace logic
{

void IntroSceneScript::OnCreate(std::shared_ptr<IScriptContext> i_scriptContext)
{
	m_introEntity = i_scriptContext->GetEntitiesFactory()->MakeIntroEntity();
	i_scriptContext->GetEntitiesManager()->AddEntity(m_introEntity);
	m_introEntity->Register();

	m_animationComponent = m_introEntity->GetComponent<AnimationComponent>(sk_animationComponentKey);
	m_cameraComponent = m_introEntity->GetComponent<CameraComponent>(sk_cameraComponentKey);
	m_audioComponent = m_introEntity->GetComponent<AudioComponent>(sk_audioComponentKey);

	m_animationComponent->SetLoop(false);
	m_onAnimationFinishedCon = m_animationComponent->sig_onAnimationFinished.Connect(
		std::bind(&IntroSceneScript::OnAnimationFinished, this)
	);

	m_cameraComponent->Register();
	m_cameraComponent->SetCameraSize(
		core::CastSize<int64_t, float>(m_animationComponent->GetSpriteSizeInFrame(0))
	);
	m_cameraComponent->Deregister();
}

void IntroSceneScript::OnDestroy()
{
	m_introEntity->Deregister();
}

void IntroSceneScript::OnAnimationFinished()
{
	if (requestReplaceSceneCallback)
	{
		requestReplaceSceneCallback(std::make_unique<SideScrollSceneScript>());
	}
}

} // namespace logic