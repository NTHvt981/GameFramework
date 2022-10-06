#pragma once
#include "Script.h"
#include "SceneScript.h"
#include "Core/Signals/Connection.h"
#include <memory>
#include <stack>

namespace logic
{

class ScenesScript : public Script
{
public:
	void OnCreate(std::shared_ptr<IScriptContext> i_scriptContext) override;
	void OnDestroy() override;
	void OnPause() override;
	void OnResume() override;
	void OnUpdate(const core::Duration& dt) override;
	void OnFixedUpdate(const core::Duration& dt) override;
	void OnRender(const core::Duration& dt) override;

private:
	void ProccessActiveScene();
	void OnSceneRequestAddScene(std::unique_ptr<SceneScript> i_scene);
	std::unique_ptr<SceneScript> m_activeScene;
	std::stack<std::unique_ptr<SceneScript>> m_pausedScenes;


};

} // namespace logic