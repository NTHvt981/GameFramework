#pragma once
#include "SceneScript.h"
#include "Core/Signals/Connection.h"

namespace logic
{

class Entity;
class AnimationComponent;

class IntroSceneScript: public SceneScript
{
public:
	void OnCreate(std::shared_ptr<IScriptContext> i_scriptContext) override;
	void OnDestroy() override;

private:
	void OnAnimationFinished();
	std::shared_ptr<Entity> m_introEntity;
	std::shared_ptr<AnimationComponent> m_animationComponent;
	signals::Connection<> m_onAnimationFinishedCon;
};

} // namespace logic