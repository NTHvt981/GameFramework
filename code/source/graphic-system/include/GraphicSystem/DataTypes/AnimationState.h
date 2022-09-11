#pragma once
#include "Core/Identifiers/AnimationId.h"
#include "GraphicSystem/DataTypes/AnimationDef.h"

namespace graphics
{

struct AnimationState
{
	enum class Direction
	{
		Normal,
		Reverse
	};

	std::weak_ptr<const AnimationDef> animationDef;
	data_types::Vector2F position;
	float alpha;
	Direction direction;
	bool pause;
};

} // namespace graphics