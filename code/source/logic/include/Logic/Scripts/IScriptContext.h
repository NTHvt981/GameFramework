#pragma once
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
	virtual std::shared_ptr<core::logic::IGameClock> GetGameClock() = 0;
	virtual std::shared_ptr<IEntitiesFactory> GetEntitiesFactory() = 0;
	virtual std::shared_ptr<EntitiesManager> GetEntitiesManager() = 0;
};

} // namespace logic