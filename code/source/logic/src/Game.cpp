#include "Logic/Game.h"
#include "Core/GameSetting/GameSetting.h"
#include "Logic/LogicSystems/GraphicSystem.h"
#include "Core/APIs/INativeGraphicAPI.h"
#include "Logic/LogicSystems/PhysicSystem.h"
#include "InputSystem/InputSystem.h"
#include "InputSystem/API/INativeInputAPI.h"
#include "AudioSystem/AudioSystem.h"
#include "AudioSystem/API/INativeAudioAPI.h"
#include "Logic/LogicSystems/FileSystem.h"
#include "Logic/Databases/Database.h"
#include "Logic/Components/ComponentsFactory.h"
#include "Logic/Entities/EntitiesFactory.h"
#include "Logic/Entities/EntitiesManager.h"
#include "Logic/Scripts/ScriptsManager.h"
#include "Logic/Scripts/ScriptContext.h"
#include "Logic/Scripts/Script.h"
#include "Logic/LogicSystems/CameraSystem/CameraSystem.h"
#include "Logic/Mailbox/Mail.h"
#include "Logic/Scenes/IntroScene.h"

namespace logic
{

////////////////////////////////////////////////////////////////////////////////

Game::Game(std::unique_ptr<core::INativeGraphicAPI> i_nativeGraphicAPI,
	std::unique_ptr<inputs::INativeInputAPI> i_nativeInputAPI,
	std::unique_ptr<audios::INativeAudioAPI> i_nativeAudioAPI,
	std::shared_ptr<core::GameSetting> i_gameSetting)
	: m_nativeGraphicAPI(std::move(i_nativeGraphicAPI))
	, m_nativeInputAPI(std::move(i_nativeInputAPI))
	, m_nativeAudioAPI(std::move(i_nativeAudioAPI))
	, m_gameSetting(i_gameSetting)
{
	m_gameClock = std::make_shared<GameClock>();
	m_fileSystem = std::make_shared<FileSystem>();
	m_database = std::make_shared<database::Database>(m_fileSystem);
	m_inputSystem = std::make_shared<inputs::InputSystem>(std::move(m_nativeInputAPI));
	m_audioSystem = std::make_shared<audios::AudioSystem>(
		std::move(m_nativeAudioAPI),
		m_database
	);
	m_graphicSystem = std::make_shared<logic::GraphicSystem>(
		std::move(m_nativeGraphicAPI),
		m_database
	);
	m_physicSystem = std::make_shared<PhysicSystem>();
	m_cameraSystem = std::make_shared<logic::camera::CameraSystem>(m_graphicSystem);

	m_componentFactory = std::make_shared<ComponentsFactory>(
		m_graphicSystem, m_inputSystem, m_audioSystem, m_physicSystem, m_cameraSystem, m_database
	);

	m_mailboxReceiveFromScene = std::make_shared<Mailbox>();

	m_entitiesFactory = std::make_shared<EntitiesFactory>(m_componentFactory);
}

////////////////////////////////////////////////////////////////////////////////

void Game::Initialize()
{
	m_fileSystem->Initialize();
	m_graphicSystem->Initialize();
	m_inputSystem->Initialize();
	m_audioSystem->Initialize();

	m_perFrameDuration = m_gameSetting->GetMillisecondsPerFrame();

	std::shared_ptr<IScene> introScene = std::make_shared<IntroScene>(m_gameClock,
		m_entitiesFactory,
		m_mailboxReceiveFromScene);
	m_scenes.push(introScene);

	m_isInitialized = true;
}

////////////////////////////////////////////////////////////////////////////////

bool Game::IsInitialized() const
{
	return m_isInitialized;
}

////////////////////////////////////////////////////////////////////////////////

void Game::LoadResource()
{
	m_database->LoadResource();
	m_graphicSystem->LoadTextures();
	m_audioSystem->LoadSounds();
}

////////////////////////////////////////////////////////////////////////////////

Game::EndLoop Game::RunLoop(const core::Duration& dt)
{
	if (m_isPaused)
	{
		return EndLoop(false);
	}

	if (m_scenes.empty())
	{
		return EndLoop(true);
	}

	UpdateInput(dt);
	Update(dt);

	m_lastFixedUpdateDuration = m_lastFixedUpdateDuration + dt;
	if (m_lastFixedUpdateDuration >= m_perFrameDuration)
	{
		FixedUpdate(m_lastFixedUpdateDuration);
		m_lastFixedUpdateDuration = 0;
	}

	Render(dt);

	ProcessMailbox();

	return EndLoop(false);
}

////////////////////////////////////////////////////////////////////////////////

void Game::Pause()
{
	m_audioSystem->Pause();
	m_inputSystem->Pause();
	m_isPaused = true;
}

////////////////////////////////////////////////////////////////////////////////

void Game::Resume()
{
	m_audioSystem->Resume();
	m_inputSystem->Resume();
	m_isPaused = false;
}

////////////////////////////////////////////////////////////////////////////////

void Game::Shutdown()
{
	m_gameClock->Shutdown();
	m_fileSystem->Shutdown();
	m_graphicSystem->Shutdown();
	m_inputSystem->Shutdown();
	m_audioSystem->Shutdown();
}

////////////////////////////////////////////////////////////////////////////////

void Game::OnResizeWindow(const core::SizeUI64& i_size)
{
}

////////////////////////////////////////////////////////////////////////////////

void Game::UpdateInput(const core::Duration& dt)
{
	m_inputSystem->UpdateInput(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::FixedUpdate(const core::Duration& dt)
{
	PreFixedUpdate(dt);
	DuringFixedUpdate(dt);
	PostFixedUpdate(dt);

	m_waitForFixedUpdate = false;
}

////////////////////////////////////////////////////////////////////////////////

void Game::PreFixedUpdate(const core::Duration& dt)
{
	m_gameClock->PreFixedUpdate(dt);
	m_physicSystem->Update(dt);
	m_scenes.front()->PreFixedUpdate(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::DuringFixedUpdate(const core::Duration& dt)
{
	m_gameClock->FixedUpdate(dt);
	m_scenes.front()->DuringFixedUpdate(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::PostFixedUpdate(const core::Duration& dt)
{
	m_gameClock->PostFixedUpdate(dt);
	m_scenes.front()->PostFixedUpdate(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::Update(const core::Duration& dt)
{
	PreUpdate(dt);
	DuringUpdate(dt);
	PostUpdate(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::PreUpdate(const core::Duration& dt)
{
	m_gameClock->PreUpdate(dt);
	m_scenes.front()->PreUpdate(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::DuringUpdate(const core::Duration& dt)
{
	m_gameClock->Update(dt);
	m_scenes.front()->DuringUpdate(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::PostUpdate(const core::Duration& dt)
{
	m_gameClock->PostUpdate(dt);
	m_scenes.front()->PostUpdate(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::Render(const core::Duration& dt)
{
	if (m_waitForFixedUpdate)
	{
		return;
	}

	PreRender(dt);
	DuringRender(dt);
	PostRender(dt);

	m_waitForFixedUpdate = true;
}

////////////////////////////////////////////////////////////////////////////////

void Game::PreRender(const core::Duration& dt)
{
	m_graphicSystem->PreRender(dt);
	m_gameClock->PreRender(dt);
	m_scenes.front()->PreRender(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::DuringRender(const core::Duration& dt)
{
	m_graphicSystem->Render(dt);
	m_gameClock->Render(dt);
	m_scenes.front()->DuringRender(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::PostRender(const core::Duration& dt)
{
	m_graphicSystem->PostRender(dt);
	m_gameClock->PostRender(dt);
	m_scenes.front()->PostRender(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::ProcessMailbox()
{
	while (!m_mailboxReceiveFromScene->IsEmpty())
	{
		std::shared_ptr<Mail> mail = m_mailboxReceiveFromScene->Receive();
		if (auto popSceneMail = std::static_pointer_cast<PopSceneMail>(mail))
		{
			m_scenes.front()->OnDestroy();
			m_scenes.pop();
		}
		else if (auto pushSceneMail = std::static_pointer_cast<PushSceneMail>(mail))
		{

		}
	}
}

////////////////////////////////////////////////////////////////////////////////

} // namespace logic