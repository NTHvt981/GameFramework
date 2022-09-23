#include "Logic/Game.h"
#include "GraphicSystem/GraphicSystem.h"
#include "PhysicSystem/PhysicSystem.h"
#include "InputSystem/InputSystem.h"
#include "FileSystem/FileSystem.h"
#include "Database/Database.h"

namespace logic
{

////////////////////////////////////////////////////////////////////////////////

Game::Game(std::unique_ptr<graphics::INativeGraphicAPI> i_nativeGraphicAPI,
	std::unique_ptr<input::INativeInputAPI> i_nativeInputAPI)
	: m_nativeGraphicAPI(std::move(i_nativeGraphicAPI))
	, m_nativeInputAPI(std::move(i_nativeInputAPI))
{
	m_gameSetting = std::make_shared<core::GameSetting>();
	
	m_gameClock = std::make_shared<logic::GameClock>();
	m_fileSystem = std::make_shared<files::FileSystem>();
	m_database = std::make_shared<database::Database>(m_fileSystem);
	m_graphicSystem = std::make_shared<graphics::GraphicSystem>(m_nativeGraphicAPI, m_database);
	m_physicSystem = std::make_shared<physics::PhysicSystem>(m_gameClock);
	m_inputSystem = std::make_shared<input::InputSystem>(m_nativeInputAPI);
}

////////////////////////////////////////////////////////////////////////////////

void Game::Initialize()
{
	m_fileSystem->Initialize();
	m_graphicSystem->Initialize();
	m_inputSystem->Initialize();

	m_millisecondsPerFrame = m_gameSetting->GetMillisecondsPerFrame();

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
}

////////////////////////////////////////////////////////////////////////////////

void Game::RunLoop(uint64_t dt)
{
	if (m_isPaused)
	{
		return;
	}

	UpdateInput(dt);
	Update(dt);

	m_millisecondsSinceLastFixedUpdate += dt;
	if (m_millisecondsSinceLastFixedUpdate >= m_millisecondsPerFrame)
	{
		FixedUpdate(m_millisecondsSinceLastFixedUpdate);
		m_millisecondsSinceLastFixedUpdate = 0;
	}

	Render(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::Pause()
{
	m_inputSystem->Pause();
	m_isPaused = true;
}

////////////////////////////////////////////////////////////////////////////////

void Game::Resume()
{
	m_inputSystem->Resume();
	m_isPaused = false;
}

////////////////////////////////////////////////////////////////////////////////

void Game::UnLoadResource()
{
}

////////////////////////////////////////////////////////////////////////////////

void Game::Shutdown()
{
	UnLoadResource();

	m_graphicSystem->Shutdown();
	m_gameClock->ShutDown();
	m_fileSystem->ShutDown();
	m_inputSystem->Shutdown();
}

////////////////////////////////////////////////////////////////////////////////

void Game::UpdateInput(const uint64_t dt)
{
	m_inputSystem->UpdateInput(dt);
	m_gameClock->UpdateInput(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::FixedUpdate(const uint64_t dt)
{
	PreFixedUpdate(dt);
	DuringFixedUpdate(dt);
	PostFixedUpdate(dt);

	m_waitForFixedUpdate = false;
}

////////////////////////////////////////////////////////////////////////////////

void Game::PreFixedUpdate(const uint64_t dt)
{
	m_gameClock->PreFixedUpdate(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::DuringFixedUpdate(const uint64_t dt)
{
	m_gameClock->FixedUpdate(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::PostFixedUpdate(const uint64_t dt)
{
	m_gameClock->PostFixedUpdate(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::Update(const uint64_t dt)
{
	PreUpdate(dt);
	DuringUpdate(dt);
	PostUpdate(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::PreUpdate(const uint64_t dt)
{
	m_gameClock->PreUpdate(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::DuringUpdate(const uint64_t dt)
{
	m_gameClock->Update(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::PostUpdate(const uint64_t dt)
{
	m_gameClock->PostUpdate(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::Render(const uint64_t dt)
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

void Game::PreRender(const uint64_t dt)
{
	m_graphicSystem->PreRender(dt);
	m_gameClock->PreRender(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::DuringRender(const uint64_t dt)
{
	m_graphicSystem->Render(dt);
	m_gameClock->Render(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::PostRender(const uint64_t dt)
{
	m_graphicSystem->PostRender(dt);
	m_gameClock->PostRender(dt);
}

////////////////////////////////////////////////////////////////////////////////

void Game::OnRequestShutdown()
{
	sig_requestShutdown.Emit();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace logic