#pragma once
#include "Logic/Scripts/Script.h"
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
	void OnCreate(core::Ref<IScriptContext> i_scriptContext) override;
	void OnDestroy() override;
	void OnFixedUpdate(const core::Duration& dt) override;

private:
	std::shared_ptr<Entity> m_wormEntity;
	std::shared_ptr<TransformCompositionComponent> m_transformComponent;
	std::shared_ptr<KinematicBodyComponent> m_kinematicComponent;
	std::shared_ptr<AnimationComponent> m_animationComponent;

	signals::Connection<core::Vector2F> m_moveCon;
};

} // namespace logic