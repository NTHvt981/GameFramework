#include "Logic/Factories/EntityFactory.h"
#include "Logic/ComponentKeys/WormKeys.h"
#include "Logic/Components/TagComponents.h"
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
#include "PhysicSystem/DataTypes/DynamicCollider.h"

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
		entityId
	);

	physics::DynamicCollider detectorCollider(entityId);
	std::shared_ptr<KinematicBodyComponent> detectorComponent = m_componentFactory->MakeKinematicBodyComponent(
		entityId
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

	std::shared_ptr<AnimationComponent> tagComponent = m_componentFactory->MakeAnimationComponent();

	Entity result(entityId);
	result.InsertComponent(sk_transformCompositionComponentKey, transformCompositionComponent);
	result.InsertComponent(sk_kinematicBodyComponentKey, bodyComponent);
	result.InsertComponent(sk_animationComponentKey, aniComponent);
	result.InsertComponent(worm::sk_detectorComponentKey, detectorComponent);
	result.InsertComponent(sk_enemyTagComponentKey, m_componentFactory->MakeEnemyTagComponent());

	return std::make_shared<Entity>(result);
}

} // namespace logic