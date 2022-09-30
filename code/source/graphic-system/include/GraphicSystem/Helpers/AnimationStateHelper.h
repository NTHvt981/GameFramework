#pragma once
#include "GraphicSystem/DataTypes/AnimationState.h"
#include "Core/DataTypes/Duration.h"
#include <stdint.h>

namespace graphics
{

void SetAnimationDef(AnimationState& i_animationState, std::shared_ptr<const AnimationDef> i_animationDef);

void UpdateAnimationState(AnimationState& i_animationState, const core::Duration& dt);

std::weak_ptr<const SpriteDef> GetCurrentSpriteDefFromAnimationState(const AnimationState& i_animationState);

} // namespace graphics