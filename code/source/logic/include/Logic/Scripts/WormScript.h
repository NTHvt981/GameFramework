#pragma once
#include "Script.h"
#include "Core/GameClock/IGameClock.h"
#include "Core/Signals/Connection.h"
#include "Logic/Entities/Entity.h"
#include "Logic/Components/TransformCompositionComponent.h"
#include "Logic/Components/KinematicBodyComponent.h"
#include "Logic/Components/AnimationComponent.h"
#include "Core/Signals/Connection.h"
#include <memory>

namespace logic
{

class WormScript final: public Script
{
public:
	// Inherited via Script
	void Initialize(std::shared_ptr<IScriptContext> i_scriptContext) override;
	void Shutdown() override;

private:
	void OnFixedUpdate(const const core::Duration& dt);
	void OnUpdate(const const core::Duration& dt);

	signals::Connection<const core::Duration&> m_onFixedUpdateCon;
	signals::Connection<const core::Duration&> m_onUpdateCon;

	std::shared_ptr<Entity> m_wormEntity;
	std::shared_ptr<TransformCompositionComponent> m_transformComponent;
	std::shared_ptr<KinematicBodyComponent> m_kinematicComponent;
	std::shared_ptr<AnimationComponent> m_animationComponent;

	signals::Connection<core::Vector2F> m_moveCon;
};

} // namespace logic