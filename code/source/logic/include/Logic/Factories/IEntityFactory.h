#pragma once
#include "Logic/Entities/Entity.h"
#include <memory>

namespace logic
{

class IEntityFactory
{
public:
	virtual std::shared_ptr<Entity> MakeWormEntity() = 0;
};

} // namespace logic