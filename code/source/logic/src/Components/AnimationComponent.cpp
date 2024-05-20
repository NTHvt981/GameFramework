#include "Logic/Components/AnimationComponent.h"
#include "GraphicSystem/DataTypes/AnimationState.h"
#include "GraphicSystem/Helpers/AnimationStateHelper.h"
#include "GraphicSystem/API/IAnimationGraphicAPI.h"
#include "GraphicSystem/Database/IGraphicDatabaseAPI.h"
#include "Core/Helpers/SizeBoxHelper.h"

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
	if (m_isRegistered)
	{
		return;
	}
	m_isRegistered = true;

	m_animationGraphicAPI.RegisterAnimation(m_animationState);

	m_onAnimationFinishedCon = m_animationState->sig_onAnimationFinished.Connect(
		std::bind(&AnimationComponent::OnAnimationFinished, this)
	);
}

void AnimationComponent::Deregister()
{
	if (!m_isRegistered)
	{
		return;
	}
	m_isRegistered = false;

	m_animationGraphicAPI.DeregisterAnimation(m_animationState->id);

	m_onAnimationFinishedCon.Disconnect();
}

void AnimationComponent::Update(const core::Duration& dt)
{
	if (m_animationState->pause)
	{
		return;
	}

	uint64_t& currentFrameIndex = m_animationState->currentFrameIndex;
	core::Duration& currentDuration = m_animationState->currentDuration;
	auto animationDef = m_animationState->animationDef.lock();

	const core::Duration calculatedDt = dt * m_animationState->speed;
	core::Duration newDuration = currentDuration + calculatedDt;
	const graphics::AnimationFrameDef& currentFrame = animationDef->frames[currentFrameIndex];
	if (newDuration >= currentFrame.duration)
	{
		currentDuration = newDuration - currentFrame.duration;
		currentFrameIndex++;
		auto frameSize = animationDef->frames.size();
		if (currentFrameIndex >= frameSize)
		{
			if (m_animationState->loop)
			{
				currentFrameIndex = 0;
				m_animationState->sig_onAnimationFinished.Emit();
			}
			else
			{
				if (!m_animationState->hasFinished)
				{
					m_animationState->sig_onAnimationFinished.Emit();
					m_animationState->hasFinished = true;
				}
				currentFrameIndex = frameSize - 1;
			}
		}

		const graphics::AnimationFrameDef& newFrame = animationDef->frames[currentFrameIndex];
		m_animationState->spriteStateRef->spriteDef = newFrame.spriteDefRef;
	}
	else
	{
		currentDuration = newDuration;
	}
}

void AnimationComponent::SetAnimation(const core::AnimationId i_animationId)
{
	std::shared_ptr<const graphics::AnimationDef> animationDef = m_graphicDatabaseAPI.GetAnimationRef(i_animationId).lock();

	m_animationState->animationDef = animationDef;
	const graphics::AnimationFrameDef& currentFrame = animationDef->frames[m_animationState->currentFrameIndex];
	m_animationState->spriteStateRef->spriteDef = currentFrame.spriteDefRef;
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

float AnimationComponent::GetSpeed() const
{
	return m_animationState->speed;
}

void AnimationComponent::SetSpeed(float i_speed)
{
	m_animationState->speed = i_speed;
}

core::SizeI64 AnimationComponent::GetSpriteSizeInFrame(uint64_t i_frameIndex)
{
	std::shared_ptr<const graphics::AnimationDef> animationDef = m_animationState->animationDef.lock();
	std::shared_ptr<const graphics::SpriteDef> spriteDef = animationDef->frames[i_frameIndex].spriteDefRef.lock();
	return core::ToSize<int64_t>(spriteDef->textureBoundary);
}

void AnimationComponent::OnAnimationFinished()
{
	sig_onAnimationFinished.Emit();
}

} // namespace logic