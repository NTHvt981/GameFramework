#pragma once
#include "Logic/Scripts/Script.h"
#include "Core/Signals/Connection.h"
#include "Core/DataTypes/Vector2.h"
#include "Logic/Components/CameraComponent.h"
#include "Logic/Components/AudioComponent.h"
#include <memory>

namespace logic
{

class Entity;
class AnimationComponent;

class IntroScript final: public Script
{
public:
	// Inherited via Script
	void OnCreate(core::Ref<IScriptContext> i_scriptContext) override;
	void OnDestroy() override;
	void OnFixedUpdate(const core::Duration& dt) override;
	~IntroScript();

	signals::Signal<> sig_onIntroFinished;
private:
	void OnAnimationFinished();

	std::shared_ptr<Entity> m_introEntity;
	std::shared_ptr<AudioComponent> m_audioComponent;
	std::shared_ptr<CameraComponent> m_cameraComponent;
	std::shared_ptr<AnimationComponent> m_animationComponent;

	signals::Connection<> m_animationFinishedCon;
};

} // namespace logic