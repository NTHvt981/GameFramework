#include "Logic/Factories/ComponentFactory.h"

namespace logic
{

ComponentFactory::ComponentFactory(
	std::shared_ptr<graphics::IGraphicSystem> i_graphicSystem,
	std::shared_ptr<input::IInputSystem> i_inputSystem,
	std::shared_ptr<audios::IAudioSystem> i_audioSystem,
	std::shared_ptr<physics::IPhysicSystem> i_physicSystem,
	std::shared_ptr<database::IDatabase> i_database)
	: m_physicSystem(i_physicSystem)
	, m_graphicSystem(i_graphicSystem)
	, m_audioSystem(i_audioSystem)
	, m_inputSystem(i_inputSystem)
	, m_database(i_database)
{
}

ComponentFactory::~ComponentFactory()
{
}

std::shared_ptr<TransformComponent> ComponentFactory::MakeTransformComponent()
{
	return std::make_shared<TransformComponent>();
}

std::shared_ptr<AnimationComponent> ComponentFactory::MakeAnimationComponent()
{
	return std::make_shared<AnimationComponent>(
		m_graphicSystem,
		m_database
	);
}

std::shared_ptr<SpriteComponent> ComponentFactory::MakeSpriteComponent()
{
	return std::make_shared<SpriteComponent>(
		m_graphicSystem,
		m_database
	);
}

std::shared_ptr<InputComponent> ComponentFactory::MakeInputComponent()
{
	return std::make_shared<InputComponent>(m_inputSystem);
}

std::shared_ptr<AudioComponent> ComponentFactory::MakeAudioComponent()
{
	return std::make_shared<AudioComponent>(m_audioSystem);
}

std::shared_ptr<KinematicBodyComponent> ComponentFactory::MakeKinematicBodyComponent(const core::EntityId i_entityId)
{
	return std::make_shared<KinematicBodyComponent>(
		m_physicSystem,
		i_entityId
	);
}

std::shared_ptr<PivotComponent> ComponentFactory::MakePivotComponent(std::shared_ptr<ITransformComponent> i_child)
{
	return std::make_shared<PivotComponent>(i_child);
}

std::shared_ptr<TransformCompositionComponent> ComponentFactory::MakeTransformCompositionComponent(
	std::initializer_list<std::shared_ptr<ITransformComponent>> i_componentList)
{
	return std::make_shared<TransformCompositionComponent>(i_componentList);
}

std::shared_ptr<EnemyTagComponent> ComponentFactory::MakeEnemyTagComponent()
{
	return std::shared_ptr<EnemyTagComponent>();
}

std::shared_ptr<PlayerTagComponent> ComponentFactory::MakePlayerTagComponent()
{
	return std::shared_ptr<PlayerTagComponent>();
}

std::shared_ptr<BulletTagComponent> ComponentFactory::MakeBulletTagComponent()
{
	return std::shared_ptr<BulletTagComponent>();
}

} // namespace logic