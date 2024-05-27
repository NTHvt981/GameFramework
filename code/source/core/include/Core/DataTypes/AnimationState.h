#pragma once
#include "Core/Identifiers/AnimationId.h"
#include "Core/DataTypes/AnimationDef.h"
#include "Core/DataTypes/SpriteState.h"
#include "Core/Signals/Signal.h"
#include "Core/DataTypes/Duration.h"
#include <memory>

namespace core
{

struct AnimationState
{
	using Id = uint64_t;
	const Id id;
	AnimationState(Id i_id) 
		: id(i_id) 
		, spriteStateRef(std::make_shared<SpriteState>(i_id))
	{

	};

	std::weak_ptr<const AnimationDef> animationDef;
	std::shared_ptr<SpriteState> spriteStateRef;
	uint64_t currentFrameIndex = 0;
	core::Duration currentDuration = 0;
	enum class Direction
	{
		Normal,
		Reverse
	};
	Direction direction = Direction::Normal;
	bool pause = false;
	bool loop = true;
	float speed = 1.0f;

	signals::Signal<> sig_onAnimationFinished;
	bool hasFinished = false; // Only used if not loop
};

} // namespace core