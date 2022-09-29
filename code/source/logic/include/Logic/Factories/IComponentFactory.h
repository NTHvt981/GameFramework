#pragma once
#include "Core/DataTypes/Vector2.h"
#include "Logic/Components/AnimationComponent.h"
#include "Logic/Components/SpriteComponent.h"
#include "Logic/Components/TransformCompositionComponent.h"
#include "Logic/Components/KinematicBodyComponent.h"
#include "Logic/Components/TransformComponent.h"
#include "Logic/Components/PivotComponent.h"
#include "Logic/Components/TransformComponent.h"
#include <memory>

namespace logic
{
	
class IComponentFactory
{
public:
	virtual std::shared_ptr<TransformComponent> MakeTransformComponent() = 0;
	virtual std::shared_ptr<AnimationComponent> MakeAnimationComponent() = 0;
	virtual std::shared_ptr<SpriteComponent> MakeSpriteComponent() = 0;
	virtual std::shared_ptr<KinematicBodyComponent> MakeKinematicBodyComponent(
		std::shared_ptr<physics::DynamicCollider> i_dynamicCollider
	) = 0;
	virtual std::shared_ptr<PivotComponent> MakePivotComponent(
		std::shared_ptr<ITransformComponent> i_child
	) = 0;
	virtual std::shared_ptr<TransformCompositionComponent> MakeTransformCompositionComponent(
		std::initializer_list<std::shared_ptr<ITransformComponent>> i_componentList
	) = 0;
};


} // namespace logic