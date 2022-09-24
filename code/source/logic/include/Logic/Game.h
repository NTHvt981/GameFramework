#pragma once
#include "GameClock.h"
#include "Core/GameSetting/GameSetting.h"
#include "GraphicSystem/IGraphicSystem.h"
#include "PhysicSystem/IPhysicSystem.h"
#include "InputSystem/IInputSystem.h"
#include "GraphicSystem/API/INativeGraphicAPI.h"
#include "InputSystem/API/INativeInputAPI.h"
#include "FileSystem/IFileSystem.h"
#include "Database/IDatabase.h"
#include <memory>

namespace logic
{

class Game
{
public:
	Game(
		std::unique_ptr<graphics::INativeGraphicAPI> i_nativeGraphicAPI,
		std::unique_ptr<input::INativeInputAPI> i_nativeInputAPI
	);
	void Initialize();
	bool IsInitialized() const;
	void LoadResource();
	void RunLoop(uint64_t dt);
	void Pause();
	void Resume();
	void UnLoadResource();
	void Shutdown();

	signals::Signal<> sig_requestShutdown;
private:
	void UpdateInput(const uint64_t dt);

	void FixedUpdate(const uint64_t dt);
	void PreFixedUpdate(const uint64_t dt);
	void DuringFixedUpdate(const uint64_t dt);
	void PostFixedUpdate(const uint64_t dt);

	void Update(const uint64_t dt);
	void PreUpdate(const uint64_t dt);
	void DuringUpdate(const uint64_t dt);
	void PostUpdate(const uint64_t dt);

	void Render(const uint64_t dt);
	void PreRender(const uint64_t dt);
	void DuringRender(const uint64_t dt);
	void PostRender(const uint64_t dt);

	void OnRequestShutdown();

	// own, self init
	std::shared_ptr<GameClock> m_gameClock;
	std::shared_ptr<files::IFileSystem> m_fileSystem;
	std::shared_ptr<graphics::IGraphicSystem> m_graphicSystem;
	std::shared_ptr<physics::IPhysicSystem> m_physicSystem;
	std::shared_ptr<input::IInputSystem> m_inputSystem;
	std::shared_ptr<core::GameSetting> m_gameSetting;
	std::shared_ptr<database::IDatabase> m_database;

	// own, pass by param
	std::shared_ptr<graphics::INativeGraphicAPI> m_nativeGraphicAPI;
	std::shared_ptr<input::INativeInputAPI> m_nativeInputAPI;

	// game clock relate
	uint64_t m_millisecondsPerFrame = 0;
	uint64_t m_millisecondsSinceLastFixedUpdate = 0;
	bool m_waitForFixedUpdate = false;

	// others
	bool m_isInitialized = false;
	bool m_isPaused = false;
};

} // namespace logic