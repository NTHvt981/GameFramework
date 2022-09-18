#include "Logic/Game.h"

namespace logic
{

Game::Game(std::unique_ptr<graphics::INativeRenderAPI> i_nativeRenderAPI)
	: m_nativeRenderAPI(std::move(i_nativeRenderAPI))
{
	m_gameClock = std::make_shared<logic::GameClock>();
	m_fileSystem = std::make_shared<files::FileSystem>();
	m_graphicSystem = std::make_shared<graphics::GraphicSystem>(m_gameClock, m_fileSystem, m_nativeRenderAPI);
}

void Game::Initialize()
{
	m_fileSystem->Initialize();
	m_graphicSystem->Initialize();

	LoadResource();
}

void Game::LoadResource()
{
}

void Game::RunLoop(uint64_t dt)
{
}

void Game::UnLoadResource()
{
}

void Game::Shutdown()
{
	UnLoadResource();

	m_graphicSystem->Shutdown();
	m_gameClock->ShutDown();
	m_fileSystem->ShutDown();
}

void Game::OnRequestShutdown()
{
	sig_requestShutdown.Emit();
}
} // namespace logic