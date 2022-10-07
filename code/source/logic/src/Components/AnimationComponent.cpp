#include "Logic/Components/AnimationComponent.h"
#include "GraphicSystem/DataTypes/AnimationState.h"
#include "GraphicSystem/Helpers/AnimationStateHelper.h"
#include "GraphicSystem/API/IAnimationGraphicAPI.h"
#include "GraphicSystem/Database/IGraphicDatabaseAPI.h"

namespace logic
{

AnimationComponent::AnimationComponent(
	std::shared_ptr<graphics::IAnimationGraphicAPI> i_animationGraphicAPI,
	std::shared_ptr<const graphics::database::IGraphicDatabaseAPI> i_graphicDatabaseAPI)
	: m_animationGraphicAPI(*i_animationGraphicAPI.get())
	, m_graphicDatabaseAPI(*i_graphicDatabaseAPI.get())
	, m_animationState(std::make_shared<graphics::AnimationState>(
		i_animationGraphicAPI->GenerateAnimationStateId()
	))
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

	m_animationGraphicAPI.RegisterAnimation(m_animationState);

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

	m_animationGraphicAPI.DeregisterAnimation(m_animationState->id);

	m_onAnimationFinishedCon.Disconnect();
}

void AnimationComponent::SetAnimation(const core::AnimationId i_animationId)
{
	std::shared_ptr<const graphics::AnimationDef> animationDef = m_graphicDatabaseAPI.GetAnimationRef(i_animationId).lock();

	graphics::SetAnimationDef(*m_animationState.get(), animationDef);
}

core::AnimationId AnimationComponent::GetAnimationId() const
{
	return m_animationState->animationDef.lock()->id;
}

bool AnimationComponent::IsLoop()
{
	return m_animationState->loop;
}

void AnimationComponent::SetLoop(bool i_value)
{
	m_animationState->loop = i_value;
}

void AnimationComponent::OnAnimationFinished()
{
	sig_onAnimationFinished.Emit();
}

} // namespace logic