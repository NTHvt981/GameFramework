#include "Logic/Factories/EntityFactory.h"

namespace logic
{

EntityFactory::EntityFactory(std::shared_ptr<IComponentFactory> i_componentFactory)
	: m_componentFactory(i_componentFactory)
{
}

std::shared_ptr<WormEntity> EntityFactory::MakeWormEntity()
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

	std::shared_ptr<CompositionComponent> rootComponent = m_componentFactory->MakeCompositionComponent(
		{
			bodyComponent,
			detectorComponent,
			moveRightAnimationComponent,
		}
	);

	WormEntity result(entityId, rootComponent);
	result.body = bodyComponent;
	result.detectorBody = detectorComponent;
	result.animation = moveRightAnimationComponent;

	return std::make_shared<WormEntity>(result);
}

} // namespace logic