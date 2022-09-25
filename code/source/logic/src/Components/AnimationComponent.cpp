#include "Logic/Components/AnimationComponent.h"

namespace logic
{

AnimationComponent::AnimationComponent(
	std::weak_ptr<graphics::IAnimationGraphicAPI> i_animationGraphicAPI,
	const core::AnimationId i_animationId)
	: m_animationGraphicAPI(i_animationGraphicAPI)
	, m_animationId(i_animationId)
{
}

AnimationComponent::~AnimationComponent()
{
	Deregister();
}

void AnimationComponent::SetPosition(const core::Vector2F& i_position)
{
	m_animationState->spriteStateRef->position = i_position;
}

core::Vector2F AnimationComponent::GetPosition() const
{
	return m_animationState->spriteStateRef->position;
}

void AnimationComponent::Register()
{
	if (isRegistered)
	{
		return;
	}
	isRegistered = true;

	std::shared_ptr<graphics::IAnimationGraphicAPI> graphicAPI = m_animationGraphicAPI.lock();
	m_animationState = graphicAPI->RegisterAnimation(m_animationId).lock();

	m_onAnimationFinishedCon = m_animationState->sig_onAnimationFinished.Connect(
		std::bind(&AnimationComponent::OnAnimationFinished, this)
	);
}

void AnimationComponent::Deregister()
{
	if (!isRegistered)
	{
		return;
	}
	isRegistered = false;

	std::shared_ptr<graphics::IAnimationGraphicAPI> graphicAPI = m_animationGraphicAPI.lock();
	graphicAPI->DeregisterAnimation(m_animationState->id);

	m_onAnimationFinishedCon.Disconnect();
}

void AnimationComponent::OnAnimationFinished()
{
	sig_onAnimationFinished.Emit();
}

} // namespace logic