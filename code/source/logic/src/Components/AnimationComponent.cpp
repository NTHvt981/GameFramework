#include "Logic/Components/AnimationComponent.h"

namespace logic
{

AnimationComponent::AnimationComponent(
	std::weak_ptr<graphics::IAnimationGraphicAPI> i_animationGraphicAPI,
	std::weak_ptr<const graphics::database::IGraphicDatabaseAPI> i_graphicDatabaseAPI,
	core::AnimationId i_animationId)
	: m_animationGraphicAPI(i_animationGraphicAPI)
	, m_graphicDatabaseAPI(i_graphicDatabaseAPI)
	, m_animationId(i_animationId)
{
}

AnimationComponent::~AnimationComponent()
{
	Deregister();
}

void AnimationComponent::SetPosition(core::Vector2F i_position)
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

void AnimationComponent::SetVisible(const bool i_visible)
{
	m_animationState->spriteStateRef->visible = i_visible;
}

bool AnimationComponent::GetVisible() const
{
	return m_animationState->spriteStateRef->visible;
}

void AnimationComponent::SetAnimation(const core::AnimationId i_animationId)
{
	std::shared_ptr<const graphics::database::IGraphicDatabaseAPI> graphicDatabaseAPI = m_graphicDatabaseAPI.lock();
	std::shared_ptr<const graphics::AnimationDef> animationDef = graphicDatabaseAPI->GetAnimationRef(i_animationId).lock();

	m_animationId = i_animationId;
	m_animationState->animationDef = animationDef;
	m_animationState->spriteStateRef->spriteDef = animationDef->frames[0].spriteRef;
}

core::AnimationId AnimationComponent::GetAnimationId() const
{
	return m_animationId;
}

void AnimationComponent::OnAnimationFinished()
{
	sig_onAnimationFinished.Emit();
}

} // namespace logic