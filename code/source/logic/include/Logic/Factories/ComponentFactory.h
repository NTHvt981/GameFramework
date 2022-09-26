#pragma once
#include "IComponentFactory.h"
#include "PhysicSystem/IPhysicSystem.h"
#include "GraphicSystem/IGraphicSystem.h"
#include "Database/IDatabase.h"

namespace logic
{

class ComponentFactory final: public IComponentFactory
{
public:
	ComponentFactory(
		std::shared_ptr<graphics::IGraphicSystem> i_graphicSystem,
		std::shared_ptr<physics::IPhysicSystem> i_physicSystem,
		std::shared_ptr<database::IDatabase> i_database
	);
	~ComponentFactory();

	std::shared_ptr<TransformComponent> MakeTransformComponent(const core::Vector2F i_position = core::Vector2F()) override;

	std::shared_ptr<AnimationComponent> MakeAnimationComponent(const core::AnimationId i_animationId) override;

	std::shared_ptr<SpriteComponent> MakeSpriteComponent(const core::SpriteId i_spriteId) override;

	std::shared_ptr<KinematicBodyComponent> MakeKinematicBodyComponent(std::shared_ptr<physics::DynamicCollider> i_dynamicCollider) override;

	std::shared_ptr<PivotComponent> MakePivotComponent(
		std::shared_ptr<PositionSetterComponent> i_component,
		const core::Vector2F i_position = core::Vector2F()
	) override;

	std::shared_ptr<CompositionComponent> MakeCompositionComponent(
		std::initializer_list<std::shared_ptr<PositionSetterComponent>> i_componentList
	) override;

	virtual std::shared_ptr<RootComponent> MakeRootComponent() override;

private:
	std::shared_ptr<physics::IPhysicSystem> m_physicSystem;
	std::shared_ptr<graphics::IGraphicSystem> m_graphicSystem;
	std::shared_ptr<database::IDatabase> m_database;
};

} // namespace logic