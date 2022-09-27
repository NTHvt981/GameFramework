#include "Logic/Components/SpriteComponent.h"

namespace logic
{

SpriteComponent::SpriteComponent(
	std::weak_ptr<graphics::ISpriteGraphicAPI> i_spriteGraphicAPI,
	const core::SpriteId i_spriteId)
	: m_spriteGraphicAPI(i_spriteGraphicAPI)
	, m_spriteId(i_spriteId)
{
}

SpriteComponent::~SpriteComponent()
{
	Deregister();
}

void SpriteComponent::SetPosition(const core::Vector2F& i_position)
{
	m_spriteState->position = i_position;
}

core::Vector2F SpriteComponent::GetPosition() const
{
	return m_spriteState->position;
}

void SpriteComponent::Register()
{
	if (isRegistered)
	{
		return;
	}
	isRegistered = true;

	std::shared_ptr<graphics::ISpriteGraphicAPI> graphicAPI = m_spriteGraphicAPI.lock();
	m_spriteState = graphicAPI->RegisterSprite(m_spriteId).lock();
}

void SpriteComponent::Deregister()
{
	if (!isRegistered)
	{
		return;
	}
	isRegistered = false;

	std::shared_ptr<graphics::ISpriteGraphicAPI> graphicAPI = m_spriteGraphicAPI.lock();
	graphicAPI->DeregisterSprite(m_spriteState->id);
}

void SpriteComponent::SetVisible(const bool i_visible)
{
	m_spriteState->visible = i_visible;
}

bool SpriteComponent::GetVisible() const
{
	return m_spriteState->visible;
}

} // namespace logic