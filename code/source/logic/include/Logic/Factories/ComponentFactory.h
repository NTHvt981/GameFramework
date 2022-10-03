#pragma once
#include "IComponentFactory.h"

namespace graphics
{
class IGraphicSystem;
} // namespace graphics

namespace inputs
{
class IInputSystem;
} // namespace inputs

namespace audios
{
class IAudioSystem;
} // namespace audios

namespace physics
{
class IPhysicSystem;
} // namespace physics

namespace database
{
class IDatabase;
} // namespace database

namespace logic
{

class ComponentFactory final: public IComponentFactory
{
public:
	ComponentFactory(
		std::shared_ptr<graphics::IGraphicSystem> i_graphicSystem,
		std::shared_ptr<inputs::IInputSystem> i_inputSystem,
		std::shared_ptr<audios::IAudioSystem> i_audioSystem,
		std::shared_ptr<physics::IPhysicSystem> i_physicSystem,
		std::shared_ptr<database::IDatabase> i_database
	);
	~ComponentFactory();

	std::shared_ptr<TransformComponent> MakeTransformComponent() override;

	std::shared_ptr<AnimationComponent> MakeAnimationComponent() override;

	std::shared_ptr<SpriteComponent> MakeSpriteComponent() override;

	std::shared_ptr<InputComponent> MakeInputComponent() override;

	std::shared_ptr<AudioComponent> MakeAudioComponent() override;

	std::shared_ptr<KinematicBodyComponent> MakeKinematicBodyComponent(const core::EntityId i_entityId) override;

	std::shared_ptr<PivotComponent> MakePivotComponent(
		std::shared_ptr<ITransformComponent> i_child
	) override;

	std::shared_ptr<TransformCompositionComponent> MakeTransformCompositionComponent(
		std::initializer_list<std::shared_ptr<ITransformComponent>> i_componentList
	) override;

	std::shared_ptr<EnemyTagComponent> MakeEnemyTagComponent() override;
	std::shared_ptr<PlayerTagComponent> MakePlayerTagComponent() override;
	std::shared_ptr<BulletTagComponent> MakeBulletTagComponent() override;

private:
	std::shared_ptr<physics::IPhysicSystem> m_physicSystem;
	std::shared_ptr<graphics::IGraphicSystem> m_graphicSystem;
	std::shared_ptr<inputs::IInputSystem> m_inputSystem;
	std::shared_ptr<audios::IAudioSystem> m_audioSystem;
	std::shared_ptr<database::IDatabase> m_database;
};

} // namespace logic