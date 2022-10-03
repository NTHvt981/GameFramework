#pragma once
#include "Core/GameClock/IGameClock.h"
#include "Logic/Factories/IEntityFactory.h"
#include "Logic/Entities/Entities.h"

namespace logic
{

/// <summary>
/// script context contains every interface needed for script
/// include GameClock, EntityFactory, EntityManager, Scene
/// </summary>
class IScriptContext
{
public:
	virtual std::shared_ptr<IEntityFactory> GetEntityFactory() = 0;
	virtual std::shared_ptr<core::logic::IGameClock> GetGameClock() = 0;
	virtual std::shared_ptr<Entities> GetEntities() = 0;
};

} // namespace logic