#pragma once
#include "Entity.h"
#include "Core/Identifiers/EntityId.h"
#include <unordered_map>
#include <memory>

namespace logic
{

using Entities = std::unordered_map<core::EntityId, std::shared_ptr<Entity>>;

} // namespace logic