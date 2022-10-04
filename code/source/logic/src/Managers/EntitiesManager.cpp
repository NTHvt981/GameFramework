#pragma once
#include "Logic/Managers/EntitiesManager.h"
#include "Logic/Entities/Entity.h"

namespace logic
{

void EntitiesManager::AddEntity(std::shared_ptr<Entity> i_entity)
{
	m_entities[i_entity->GetId()] = i_entity;
}

std::shared_ptr<Entity> EntitiesManager::GetEntity(core::EntityId i_entityId) const
{
	return m_entities.at(i_entityId);
}

} // namespace logic