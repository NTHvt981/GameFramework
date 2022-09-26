#include "Logic/Factories/EntityFactory.h"

namespace logic
{

EntityFactory::EntityFactory(std::shared_ptr<IComponentFactory> i_componentFactory)
	: m_componentFactory(i_componentFactory)
{
}

std::shared_ptr<Entity> EntityFactory::MakeWormEntity()
{
	const core::EntityId entityId = m_idGenerator.Generate();
	
	physics::DynamicCollider collider(entityId);
	collider.collisionLayer = core::CollisionLayer::Enemy;
	std::shared_ptr<KinematicBodyComponent> bodyComponent = m_componentFactory->MakeKinematicBodyComponent(
		std::make_shared<physics::DynamicCollider>(collider)
	);

	physics::DynamicCollider detectorCollider(entityId);
	std::shared_ptr<KinematicBodyComponent> detectorComponent = m_componentFactory->MakeKinematicBodyComponent(
		std::make_shared<physics::DynamicCollider>(detectorCollider)
	);

	std::shared_ptr<AnimationComponent> moveRightAnimationComponent = m_componentFactory->MakeAnimationComponent(
		core::AnimationId::WormMoveRight
	);

	std::shared_ptr<CompositionComponent> compositionComponent = m_componentFactory->MakeCompositionComponent(
		{
			bodyComponent,
			detectorComponent,
			moveRightAnimationComponent,
		}
	);

	std::shared_ptr<TransformComponent> transformComponent = m_componentFactory->MakeTransformComponent();

	std::shared_ptr<RootComponent> rootComponent = m_componentFactory->MakeRootComponent();
	rootComponent->InsertComponent("CompositionComponent", compositionComponent);
	rootComponent->InsertComponent("detectorComponent", detectorComponent);
	rootComponent->InsertComponent("bodyComponent", bodyComponent);
	rootComponent->InsertComponent("TransformComponent", transformComponent);

	Entity result
	{
		entityId, rootComponent
	};

	return std::make_shared<Entity>(result);
}

} // namespace logic