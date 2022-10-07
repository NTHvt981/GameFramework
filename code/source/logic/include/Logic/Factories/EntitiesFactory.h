#pragma once
#include "IEntitiesFactory.h"
#include "Logic/Factories/IComponentsFactory.h"
#include "Core/Generator/IncrementIdGenerator.h"

namespace logic
{

class EntitiesFactory final: public IEntitiesFactory
{
public:
	EntitiesFactory(std::shared_ptr<IComponentsFactory> i_componentFactory);

	// Inherited via IEntitiesFactory
	std::shared_ptr<Entity> MakeWormEntity() override;
	std::shared_ptr<Entity> MakeIntroEntity() override;

private:
	std::shared_ptr<IComponentsFactory> m_componentFactory;
	core::IncrementIdGenerator m_idGenerator;
};

} // namespace logic