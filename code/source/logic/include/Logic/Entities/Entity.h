#pragma once
#include "Logic/Components/RootComponent.h"
#include "Core/Identifiers/EntityId.h"
#include "Core/DataTypes/String.h"
#include <memory>

namespace logic
{

/// <summary>
/// Every entity inherit this class
/// Do not have shared_ptr of any component except root
/// </summary>
struct Entity
{
    const core::EntityId id;
    const std::shared_ptr<RootComponent> root;
};

} // namespace logic
