#pragma once
#include "Logic/Scripts/ScenesScript.h"

namespace logic
{

void ScenesScript::OnCreate(std::shared_ptr<IScriptContext> i_scriptContext)
{
}

void ScenesScript::OnDestroy()
{
}

void ScenesScript::OnPause()
{
}

void ScenesScript::OnResume()
{
}

void ScenesScript::OnUpdate(const core::Duration& dt)
{
	ProccessActiveScene();
}

void ScenesScript::OnFixedUpdate(const core::Duration& dt)
{
}

void ScenesScript::OnRender(const core::Duration& dt)
{
}

void ScenesScript::ProccessActiveScene()
{
	switch (m_activeScene->scriptState)
	{
	case core::ScriptState::Inactive:
	{
		m_pausedScenes.push(std::move(m_activeScene));
	}
	case core::ScriptState::ConfirmedDestroyed:
	{
		if (!m_pausedScenes.empty())
		{
			m_activeScene.release();
			m_activeScene = std::move(m_pausedScenes.top());
			m_activeScene->requestAddSceneCon = m_activeScene->sig_requestAddScene.Connect(
				std::bind(&ScenesScript::OnSceneRequestAddScene, this, std::placeholders::_1)
			);
			m_pausedScenes.pop();
		}
	}
	default:
		break;
	}
}

void ScenesScript::OnSceneRequestAddScene(std::unique_ptr<SceneScript> i_scene)
{
	m_pausedScenes.push(std::move(i_scene));
}

} // namespace logic