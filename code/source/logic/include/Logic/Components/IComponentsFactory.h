#pragma once
#include "Core/DataTypes/Vector2.h"
#include "Core/Identifiers/EntityId.h"
#include <memory>

namespace logic
{
class TransformComponent;
class AnimationComponent;
class SpriteComponent;
class InputComponent;
class AudioComponent;
class KinematicBodyComponent;
class CameraComponent;
class PivotComponent;
class TransformCompositionComponent;
class ITransformComponent;
class EnemyTagComponent;
class PlayerTagComponent;
class BulletTagComponent;
	
class IComponentsFactory
{
public:
	virtual std::shared_ptr<TransformComponent> MakeTransformComponent() = 0;
	virtual std::shared_ptr<AnimationComponent> MakeAnimationComponent() = 0;
	virtual std::shared_ptr<SpriteComponent> MakeSpriteComponent() = 0;
	virtual std::shared_ptr<InputComponent> MakeInputComponent() = 0;
	virtual std::shared_ptr<AudioComponent> MakeAudioComponent() = 0;
	virtual std::shared_ptr<KinematicBodyComponent> MakeKinematicBodyComponent(
		const core::EntityId i_entityId
	) = 0;
	virtual std::shared_ptr<CameraComponent> MakeCameraComponent(
		const core::EntityId i_entityId
	) = 0;
	virtual std::shared_ptr<PivotComponent> MakePivotComponent(
		std::shared_ptr<ITransformComponent> i_child
	) = 0;
	virtual std::shared_ptr<TransformCompositionComponent> MakeTransformCompositionComponent(
		std::initializer_list<std::shared_ptr<ITransformComponent>> i_componentList
	) = 0;

	// Make tags component
	virtual std::shared_ptr<EnemyTagComponent> MakeEnemyTagComponent() = 0;
	virtual std::shared_ptr<PlayerTagComponent> MakePlayerTagComponent() = 0;
	virtual std::shared_ptr<BulletTagComponent> MakeBulletTagComponent() = 0;
};


} // namespace logic