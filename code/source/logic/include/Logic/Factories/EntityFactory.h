#pragma once
#include "IEntityFactory.h"
#include "Logic/Factories/IComponentFactory.h"
#include "Core/Generator/IncrementIdGenerator.h"

namespace logic
{

class EntityFactory final: public IEntityFactory
{
public:
	EntityFactory(std::shared_ptr<IComponentFactory> i_componentFactory);

	// Inherited via IEntityFactory
	virtual std::shared_ptr<Entity> MakeWormEntity() override;

private:
	std::shared_ptr<IComponentFactory> m_componentFactory;
	core::IncrementIdGenerator m_idGenerator;
};

} // namespace logic