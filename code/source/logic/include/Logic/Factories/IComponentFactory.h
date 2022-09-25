#pragma once
#include "Core/DataTypes/Vector2.h"
#include "Logic/Components/AnimationComponent.h"
#include "Logic/Components/SpriteComponent.h"
#include "Logic/Components/CompositionComponent.h"
#include "Logic/Components/KinematicBodyComponent.h"
#include "Logic/Components/TransformComponent.h"
#include "Logic/Components/PivotComponent.h"
#include <memory>

namespace logic
{
	
class IComponentFactory
{
public:
	virtual std::shared_ptr<TransformComponent> MakeTransformComponent(const core::Vector2F i_position = core::Vector2F()) = 0;
	virtual std::shared_ptr<AnimationComponent> MakeAnimationComponent(const core::AnimationId i_animationId) = 0;
	virtual std::shared_ptr<SpriteComponent> MakeSpriteComponent(const core::SpriteId i_spriteId) = 0;
	virtual std::shared_ptr<KinematicBodyComponent> MakeKinematicBodyComponent(
		std::shared_ptr<physics::DynamicCollider> i_dynamicCollider
	) = 0;
	virtual std::shared_ptr<PivotComponent> MakePivotComponent(
		std::shared_ptr<Component> i_component,
		const core::Vector2F i_position = core::Vector2F()
	) = 0;
	virtual std::shared_ptr<CompositionComponent> MakeCompositionComponent(
		std::initializer_list<std::shared_ptr<Component>> i_componentList
	) = 0;
};


} // namespace logic