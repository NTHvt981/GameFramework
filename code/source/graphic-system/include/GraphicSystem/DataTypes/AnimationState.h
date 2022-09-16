#pragma once
#include "Core/Identifiers/AnimationId.h"
#include "GraphicSystem/DataTypes/AnimationDef.h"
#include "GraphicSystem/DataTypes/SpriteState.h"

namespace graphics
{

struct AnimationState
{
	enum class Direction
	{
		Normal,
		Reverse
	};

	using Id = uint64_t;
	Id id;
	std::weak_ptr<const AnimationDef> animationDef;
	uint64_t currentFrameIndex;
	uint64_t currentTime;
	SpriteState spriteState;
	Direction direction;
	bool pause;
};

} // namespace graphics