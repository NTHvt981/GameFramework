#include "Logic/Components/ComponentsFactory.h"
#include "Logic/LogicSystems/CameraSystem/ICameraSystem.h"
#include "Logic/LogicSystems/IGraphicSystem.h"
#include "Logic/LogicSystems/IInputSystem.h"
#include "AudioSystem/IAudioSystem.h"
#include "Logic/Databases/IDatabase.h"
#include "Logic/Components/AnimationComponent.h"
#include "Logic/Components/SpriteComponent.h"
#include "Logic/Components/InputComponent.h"
#include "Logic/Components/AudioComponent.h"
#include "Logic/Components/TransformCompositionComponent.h"
#include "Logic/Components/KinematicBodyComponent.h"
#include "Logic/Components/CameraComponent.h"
#include "Logic/Components/TransformComponent.h"
#include "Logic/Components/PivotComponent.h"
#include "Logic/Components/TransformComponent.h"
#include "Logic/Components/TagComponents.h"
#include "Core/DataTypes/Ref.h"

namespace logic
{

ComponentsFactory::ComponentsFactory(
	std::shared_ptr<IGraphicSystem> i_graphicSystem,
	std::shared_ptr<IInputSystem> i_inputSystem,
	std::shared_ptr<audios::IAudioSystem> i_audioSystem,
	std::shared_ptr<core::IPhysicAPI> i_physicAPI,
	std::shared_ptr<camera::ICameraSystem> i_cameraSystem,
	std::shared_ptr<IDatabase> i_database)
	: m_physicAPI(i_physicAPI)
	, m_cameraSystem(i_cameraSystem)
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
		m_physicAPI,
		i_entityId
	);
}

std::shared_ptr<CameraComponent> ComponentsFactory::MakeCameraComponent(const core::EntityId i_entityId)
{
	return std::make_shared<CameraComponent>(
		m_cameraSystem,
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