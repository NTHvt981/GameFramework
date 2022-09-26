#include "Logic/Factories/ComponentFactory.h"

namespace logic
{

ComponentFactory::ComponentFactory(
	std::shared_ptr<graphics::IGraphicSystem> i_graphicSystem,
	std::shared_ptr<physics::IPhysicSystem> i_physicSystem,
	std::shared_ptr<database::IDatabase> i_database)
	: m_physicSystem(i_physicSystem)
	, m_graphicSystem(i_graphicSystem)
	, m_database(i_database)
{
}

ComponentFactory::~ComponentFactory()
{
}

std::shared_ptr<TransformComponent> ComponentFactory::MakeTransformComponent(const core::Vector2F i_position)
{
	return std::make_shared<TransformComponent>(i_position);
}

std::shared_ptr<AnimationComponent> ComponentFactory::MakeAnimationComponent(const core::AnimationId i_animationId)
{
	return std::make_shared<AnimationComponent>(
		m_graphicSystem,
		m_database,
		i_animationId		
	);
}

std::shared_ptr<SpriteComponent> ComponentFactory::MakeSpriteComponent(const core::SpriteId i_spriteId)
{
	return std::make_shared<SpriteComponent>(
		m_graphicSystem,
		i_spriteId
	);
}

std::shared_ptr<KinematicBodyComponent> ComponentFactory::MakeKinematicBodyComponent(std::shared_ptr<physics::DynamicCollider> i_dynamicCollider)
{
	return std::make_shared<KinematicBodyComponent>(
		m_physicSystem,
		i_dynamicCollider
	);
}

std::shared_ptr<PivotComponent> ComponentFactory::MakePivotComponent(
	std::shared_ptr<PositionSetterComponent> i_component,
	const core::Vector2F i_position)
{
	return std::make_shared<PivotComponent>(i_component, i_position);
}

std::shared_ptr<CompositionComponent> ComponentFactory::MakeCompositionComponent(
	std::initializer_list<std::shared_ptr<PositionSetterComponent>> i_componentList)
{
	return std::make_shared<CompositionComponent>(i_componentList);
}

std::shared_ptr<RootComponent> ComponentFactory::MakeRootComponent()
{
	return std::make_shared<RootComponent>(std::map<core::String, std::shared_ptr<Component>>());
}

} // namespace logic