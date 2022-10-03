#include "Logic/Factories/ComponentsFactory.h"
#include "PhysicSystem/IPhysicSystem.h"
#include "GraphicSystem/IGraphicSystem.h"
#include "InputSystem/IInputSystem.h"
#include "AudioSystem/IAudioSystem.h"
#include "Database/IDatabase.h"
#include "Logic/Components/AnimationComponent.h"
#include "Logic/Components/SpriteComponent.h"
#include "Logic/Components/InputComponent.h"
#include "Logic/Components/AudioComponent.h"
#include "Logic/Components/TransformCompositionComponent.h"
#include "Logic/Components/KinematicBodyComponent.h"
#include "Logic/Components/TransformComponent.h"
#include "Logic/Components/PivotComponent.h"
#include "Logic/Components/TransformComponent.h"
#include "Logic/Components/TagComponents.h"

namespace logic
{

ComponentsFactory::ComponentsFactory(
	std::shared_ptr<graphics::IGraphicSystem> i_graphicSystem,
	std::shared_ptr<inputs::IInputSystem> i_inputSystem,
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

ComponentsFactory::~ComponentsFactory()
{
}

std::shared_ptr<TransformComponent> ComponentsFactory::MakeTransformComponent()
{
	return std::make_shared<TransformComponent>();
}

std::shared_ptr<AnimationComponent> ComponentsFactory::MakeAnimationComponent()
{
	return std::make_shared<AnimationComponent>(
		m_graphicSystem,
		m_database
	);
}

std::shared_ptr<SpriteComponent> ComponentsFactory::MakeSpriteComponent()
{
	return std::make_shared<SpriteComponent>(
		m_graphicSystem,
		m_database
	);
}

std::shared_ptr<InputComponent> ComponentsFactory::MakeInputComponent()
{
	return std::make_shared<InputComponent>(m_inputSystem);
}

std::shared_ptr<AudioComponent> ComponentsFactory::MakeAudioComponent()
{
	return std::make_shared<AudioComponent>(m_audioSystem);
}

std::shared_ptr<KinematicBodyComponent> ComponentsFactory::MakeKinematicBodyComponent(const core::EntityId i_entityId)
{
	return std::make_shared<KinematicBodyComponent>(
		m_physicSystem,
		i_entityId
	);
}

std::shared_ptr<PivotComponent> ComponentsFactory::MakePivotComponent(std::shared_ptr<ITransformComponent> i_child)
{
	return std::make_shared<PivotComponent>(i_child);
}

std::shared_ptr<TransformCompositionComponent> ComponentsFactory::MakeTransformCompositionComponent(
	std::initializer_list<std::shared_ptr<ITransformComponent>> i_componentList)
{
	return std::make_shared<TransformCompositionComponent>(i_componentList);
}

std::shared_ptr<EnemyTagComponent> ComponentsFactory::MakeEnemyTagComponent()
{
	return std::make_shared<EnemyTagComponent>();
}

std::shared_ptr<PlayerTagComponent> ComponentsFactory::MakePlayerTagComponent()
{
	return std::make_shared<PlayerTagComponent>();
}

std::shared_ptr<BulletTagComponent> ComponentsFactory::MakeBulletTagComponent()
{
	return std::make_shared<BulletTagComponent>();
}

} // namespace logic