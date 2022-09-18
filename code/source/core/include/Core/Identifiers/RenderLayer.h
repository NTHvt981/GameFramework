#pragma once
#include <cstdint>
#include "Core/DataTypes/Iterator.h"

namespace ids
{

enum class RenderLayer : uint64_t
{
	Default,
	Pause
};
typedef core::Iterator<RenderLayer, RenderLayer::Default, RenderLayer::Pause> RenderLayerIterator;

} // namespace ids