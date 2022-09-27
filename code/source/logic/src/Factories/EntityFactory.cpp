#include "Logic/Factories/EntityFactory.h"
#include "Logic/ComponentKeys/CommonKeys.h"
#include "Logic/ComponentKeys/WormKeys.h"

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

	std::shared_ptr<AnimationComponent> moveLeftAnimationComponent = m_componentFactory->MakeAnimationComponent(
		core::AnimationId::WormMoveLeft
	);

	std::shared_ptr<TransformCompositionComponent> transformCompositionComponent = m_componentFactory->MakeTransformCompositionComponent(
		{
			bodyComponent,
			detectorComponent,
			moveRightAnimationComponent,
			moveLeftAnimationComponent
		}
	);

	Entity result(entityId);
	result.InsertComponent(common::sk_transformCompositionComponentKey, transformCompositionComponent);
	result.InsertComponent(worm::sk_detectorComponentKey, detectorComponent);
	result.InsertComponent(common::sk_kinematicBodyComponentKey, bodyComponent);
	result.InsertComponent(worm::sk_moveLeftAnimationComponentKey, moveRightAnimationComponent);
	result.InsertComponent(worm::sk_moveRightAnimationComponentKey, moveLeftAnimationComponent);

	return std::make_shared<Entity>(result);
}

} // namespace logic