#pragma once
#include "Logic/Components/Component.h"
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
    std::shared_ptr<Component> root;
    Entity(const core::EntityId i_id, std::shared_ptr<Component> i_root) 
        : id(i_id), root(i_root) 
    {
    }

    core::String name; // this should be set by script
};

} // namespace logic
