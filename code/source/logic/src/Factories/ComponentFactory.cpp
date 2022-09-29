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

std::shared_ptr<KinematicBodyComponent> ComponentFactory::MakeKinematicBodyComponent(std::shared_ptr<physics::DynamicCollider> i_dynamicCollider)
{
	return std::make_shared<KinematicBodyComponent>(
		m_physicSystem,
		i_dynamicCollider
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

} // namespace logic