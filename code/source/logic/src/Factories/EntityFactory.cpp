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

	std::shared_ptr<AnimationComponent> aniComponent = m_componentFactory->MakeAnimationComponent();
	aniComponent->SetAnimation(core::AnimationId::WormMoveRight);

	std::shared_ptr<TransformCompositionComponent> transformCompositionComponent = m_componentFactory->MakeTransformCompositionComponent(
		{
			bodyComponent,
			detectorComponent,
			aniComponent
		}
	);

	Entity result(entityId);
	result.InsertComponent(common::sk_transformCompositionComponentKey, transformCompositionComponent);
	result.InsertComponent(common::sk_kinematicBodyComponentKey, bodyComponent);
	result.InsertComponent(common::sk_animationComponentKey, aniComponent);
	result.InsertComponent(worm::sk_detectorComponentKey, detectorComponent);

	return std::make_shared<Entity>(result);
}

} // namespace logic