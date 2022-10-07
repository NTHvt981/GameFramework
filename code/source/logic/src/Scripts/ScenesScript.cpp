#pragma once
#include "Logic/Scripts/ScenesScript.h"
#include "Logic/Scripts/IntroSceneScript.h"

namespace logic
{

void ScenesScript::OnCreate(std::shared_ptr<IScriptContext> i_scriptContext)
{
	m_activeScene = std::make_unique<IntroSceneScript>();
	m_activeScene->requestAddSceneCallback = std::bind(
		&ScenesScript::OnSceneRequestAddScene, this, std::placeholders::_1
	);
	m_activeScene->requestReplaceSceneCallback = std::bind(
		&ScenesScript::OnSceneRequestReplaceScene, this, std::placeholders::_1
	);
	requestAddScriptToManagerCallback(m_activeScene.get());
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
	if (m_activeScene == nullptr)
	{
		PopNewActiveScene();
		return;
	}

	switch (m_activeScene->scriptState)
	{
	case core::ScriptState::Inactive:
	{
		if (!m_pausedScenes.empty())
		{
			std::unique_ptr<SceneScript> temp = std::move(m_activeScene);
			m_activeScene = std::move(m_pausedScenes.top());
			m_pausedScenes.pop();
			m_pausedScenes.push(std::move(temp));

			m_activeScene->requestAddSceneCallback = std::bind(
				&ScenesScript::OnSceneRequestAddScene, this, std::placeholders::_1
			);
		}
	}
	case core::ScriptState::ConfirmedDestroyed:
	{
		PopNewActiveScene();
	}
	default:
		break;
	}
}

void ScenesScript::PopNewActiveScene()
{
	if (!m_pausedScenes.empty())
	{
		std::unique_ptr<SceneScript> temp = std::move(m_activeScene);
		m_activeScene = std::move(m_pausedScenes.top());
		m_pausedScenes.pop();
		m_pausedScenes.push(std::move(temp));

		m_activeScene->requestAddSceneCallback = std::bind(
			&ScenesScript::OnSceneRequestAddScene, this, std::placeholders::_1
		);
		m_activeScene->requestReplaceSceneCallback = std::bind(
			&ScenesScript::OnSceneRequestReplaceScene, this, std::placeholders::_1
		);
		requestAddScriptToManagerCallback(m_activeScene.get());
	}
}

void ScenesScript::OnSceneRequestAddScene(std::unique_ptr<SceneScript> i_scene)
{
	m_activeScene->scriptState = core::ScriptState::Paused;
	m_pausedScenes.push(std::move(i_scene));
}

void ScenesScript::OnSceneRequestReplaceScene(std::unique_ptr<SceneScript> i_scene)
{
	m_activeScene->scriptState = core::ScriptState::Destroyed;
	m_pausedScenes.push(std::move(i_scene));
}

} // namespace logic