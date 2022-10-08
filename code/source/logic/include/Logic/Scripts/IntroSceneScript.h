#pragma once
#include "SceneScript.h"
#include "Core/Signals/Connection.h"

namespace logic
{

class Entity;
class AnimationComponent;
class AudioComponent;
class CameraComponent;

class IntroSceneScript: public SceneScript
{
public:
	void OnCreate(std::shared_ptr<IScriptContext> i_scriptContext) override;
	void OnDestroy() override;

private:
	void OnAnimationFinished();
	std::shared_ptr<Entity> m_introEntity;
	std::shared_ptr<AnimationComponent> m_animationComponent;
	std::shared_ptr<AudioComponent> m_audioComponent;
	std::shared_ptr<CameraComponent> m_cameraComponent;
	signals::Connection<> m_onAnimationFinishedCon;
};

} // namespace logic