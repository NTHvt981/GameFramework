#pragma once
#include <cstdint>
#include "Core/DataTypes/Iterator.h"

namespace core
{

enum class RenderLayer : uint64_t
{
	Default,
	Pause
};
typedef Iterator<RenderLayer, RenderLayer::Default, RenderLayer::Pause> RenderLayerIterators;

} // namespace core