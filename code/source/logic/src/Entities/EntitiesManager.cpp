#pragma once
#include "Logic/Entities/EntitiesManager.h"
#include "Logic/Entities/Entity.h"

namespace logic
{

void EntitiesManager::AddEntity(std::shared_ptr<Entity> i_entity)
{
	m_entities[i_entity->GetId()] = i_entity;
	i_entity->SetDeregisterCallback([this, i_entity]()
		{
			RemoveEntity(i_entity->GetId());
		}
	);
}

std::shared_ptr<Entity> EntitiesManager::GetEntity(core::EntityId i_entityId) const
{
	return m_entities.at(i_entityId);
}

void EntitiesManager::RemoveEntity(core::EntityId i_entityId)
{
	m_entities[i_entityId] = nullptr;
}

} // namespace logic