#include "Logic/Components/SpriteComponent.h"
#include "GraphicSystem/API/ISpriteGraphicAPI.h"
#include "GraphicSystem/Database/IGraphicDatabaseAPI.h"
#include "GraphicSystem/DataTypes/SpriteState.h"

namespace logic
{

SpriteComponent::SpriteComponent(
	std::weak_ptr<graphics::ISpriteGraphicAPI> i_spriteGraphicAPI, 
	std::weak_ptr<const graphics::database::IGraphicDatabaseAPI> i_graphicDatabaseAPI)
	: m_spriteGraphicAPI(i_spriteGraphicAPI)
	, m_graphicDatabaseAPI(i_graphicDatabaseAPI)
	, m_spriteState(std::make_shared<graphics::SpriteState>(
		i_spriteGraphicAPI.lock()->GenerateSpriteStateId()
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

	std::shared_ptr<graphics::ISpriteGraphicAPI> graphicAPI = m_spriteGraphicAPI.lock();
	graphicAPI->RegisterSprite(m_spriteState);
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

void SpriteComponent::SetSprite(const core::SpriteId i_spriteId)
{
	m_spriteState->spriteDef = m_graphicDatabaseAPI.lock()->GetSpriteRef(i_spriteId);
}

} // namespace logic