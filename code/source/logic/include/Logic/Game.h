#pragma once
#include "GameClock.h"
#include "GraphicSystem/GraphicSystem.h"
#include "GraphicSystem/API/INativeRenderAPI.h"
#include "FileSystem/FileSystem.h"
#include "Core/Signals/Signal.h"
#include <memory>

namespace logic
{

class Game
{
public:
	Game(std::unique_ptr<graphics::INativeRenderAPI> i_nativeRenderAPI);
	void Initialize();
	void LoadResource();
	void RunLoop(uint64_t dt);
	void UnLoadResource();
	void Shutdown();

	signals::Signal<> sig_requestShutdown;
private:
	void OnRequestShutdown();

	// own, self init
	std::shared_ptr<GameClock> m_gameClock;
	std::shared_ptr<files::FileSystem> m_fileSystem;
	std::shared_ptr<graphics::GraphicSystem> m_graphicSystem;

	// own, pass by param
	std::shared_ptr<graphics::INativeRenderAPI> m_nativeRenderAPI;
};

} // namespace logic