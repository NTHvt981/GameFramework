#pragma once
#include "GraphicSystem/DataTypes/AnimationState.h"
#include "Core/DataTypes/Duration.h"
#include <stdint.h>

namespace graphics
{

void UpdateAnimationState(AnimationState& i_animationState, const core::Duration& dt);

} // namespace graphics