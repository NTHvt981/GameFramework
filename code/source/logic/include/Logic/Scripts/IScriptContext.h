#pragma once
#include "Logic/Entities/Entities.h"

namespace core::logic
{
class IGameClock;
} // namespace core::logic

namespace logic
{

class IEntitiesFactory;

/// <summary>
/// script context contains every interface needed for script
/// include GameClock, EntitiesFactory, EntityManager, Scene
/// </summary>
class IScriptContext
{
public:
	virtual std::shared_ptr<IEntitiesFactory> GetEntityFactory() = 0;
	virtual std::shared_ptr<core::logic::IGameClock> GetGameClock() = 0;
	virtual std::shared_ptr<Entities> GetEntities() = 0;
};

} // namespace logic