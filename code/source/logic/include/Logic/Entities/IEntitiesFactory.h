#pragma once
#include "Logic/Entities/Entity.h"
#include <memory>

namespace logic
{

class IEntitiesFactory
{
public:
	virtual std::shared_ptr<Entity> MakeWormEntity() = 0;
	virtual std::shared_ptr<Entity> MakeIntroEntity() = 0;
};

} // namespace logic