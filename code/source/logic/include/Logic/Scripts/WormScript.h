#pragma once
#include "Script.h"
#include "Core/Signals/Connection.h"
#include "Core/DataTypes/Vector2.h"
#include <memory>

namespace logic
{

class Entity;
class TransformCompositionComponent;
class KinematicBodyComponent;
class AnimationComponent;

class WormScript final: public Script
{
public:
	// Inherited via Script
	void OnCreate(std::shared_ptr<IScriptContext> i_scriptContext) override;
	void OnDestroy() override;
	void OnFixedUpdate(const core::Duration& dt) override;
	void OnUpdate(const core::Duration& dt) override;

	signals::Connection<const core::Duration&> m_onFixedUpdateCon;
	signals::Connection<const core::Duration&> m_onUpdateCon;

	std::shared_ptr<Entity> m_wormEntity;
	std::shared_ptr<TransformCompositionComponent> m_transformComponent;
	std::shared_ptr<KinematicBodyComponent> m_kinematicComponent;
	std::shared_ptr<AnimationComponent> m_animationComponent;

	signals::Connection<core::Vector2F> m_moveCon;
};

} // namespace logic