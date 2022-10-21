#pragma once
#include "Core/DataTypes/Ref.h"
#include <memory>

namespace core::logic
{
class IGameClock;
} // namespace core::logic

namespace logic
{

class IEntitiesFactory;
class EntitiesManager;

/// <summary>
/// script context contains every interface needed for script
/// include GameClock, EntitiesFactory, EntityManager, Scene
/// </summary>
class IScriptContext
{
public:
	virtual core::Ref<core::logic::IGameClock> GetGameClock() = 0;
	virtual core::Ref<IEntitiesFactory> GetEntitiesFactory() = 0;
	virtual core::Ref<EntitiesManager> GetEntitiesManager() = 0;
};

} // namespace logic