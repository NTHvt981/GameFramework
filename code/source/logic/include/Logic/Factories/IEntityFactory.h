#pragma once
#include "Logic/Entities/WormEntity.h"
#include <memory>

namespace logic
{

class IEntityFactory
{
public:
	virtual std::shared_ptr<WormEntity> MakeWormEntity() = 0;
};

} // namespace logic