#include "Logic/Components/SpriteComponent.h"
#include "Core/APIs/ISpriteGraphicAPI.h"
#include "Logic/Databases/IGraphicDatabaseAPI.h"
#include "Core/DataTypes/SpriteState.h"

namespace logic
{

SpriteComponent::SpriteComponent(
	std::shared_ptr<graphics::ISpriteGraphicAPI> i_spriteGraphicAPI,
	std::shared_ptr<const graphics::database::IGraphicDatabaseAPI> i_graphicDatabaseAPI)
	: m_spriteGraphicAPI(*i_spriteGraphicAPI.get())
	, m_graphicDatabaseAPI(*i_graphicDatabaseAPI.get())
	, m_spriteState(std::make_shared<graphics::SpriteState>(
		i_spriteGraphicAPI->GenerateSpriteStateId()
	))
{
}

SpriteComponent::~SpriteComponent()
{
	Deregister();
}

void SpriteComponent::SetPosition(core::Vector2F i_position)
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

	m_spriteGraphicAPI.RegisterSprite(m_spriteState);
}

void SpriteComponent::Deregister()
{
	if (!isRegistered)
	{
		return;
	}
	isRegistered = false;

	m_spriteGraphicAPI.DeregisterSprite(m_spriteState->id);
}

void SpriteComponent::SetSprite(const core::SpriteId i_spriteId)
{
	m_spriteState->spriteDef = m_graphicDatabaseAPI.GetSpriteRef(i_spriteId);
}

} // namespace logic