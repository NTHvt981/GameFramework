#pragma once
#include "Core/Identifiers/EntityId.h"
#include <unordered_map>
#include <memory>

namespace logic
{

class Entity;

class EntitiesManager
{
public:
	void AddEntity(std::shared_ptr<Entity> i_entity);
	std::shared_ptr<Entity> GetEntity(core::EntityId i_entityId) const;

private:
	void RemoveEntity(core::EntityId i_entityId);
	std::unordered_map<core::EntityId, std::shared_ptr<Entity>> m_entities;
};

} // namespace logic