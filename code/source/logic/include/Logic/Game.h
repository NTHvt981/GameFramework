#pragma once
#include "GameClock.h"
#include "Core/GameSetting/GameSetting.h"
#include "GraphicSystem/IGraphicSystem.h"
#include "PhysicSystem/IPhysicSystem.h"
#include "InputSystem/IInputSystem.h"
#include "AudioSystem/IAudioSystem.h"
#include "GraphicSystem/API/INativeGraphicAPI.h"
#include "InputSystem/API/INativeInputAPI.h"
#include "AudioSystem/API/INativeAudioAPI.h"
#include "FileSystem/IFileSystem.h"
#include "Database/IDatabase.h"
#include "Factories/IComponentFactory.h"
#include "Factories/IEntityFactory.h"
#include "Logic/Scripts/IScriptContext.h"
#include "Logic/Scripts/Script.h"
#include "Logic/LogicSystems/CameraSystem/ICameraSystem.h"
#include <memory>

namespace logic
{

class Game
{
public:
	Game(
		std::unique_ptr<graphics::INativeGraphicAPI> i_nativeGraphicAPI,
		std::unique_ptr<inputs::INativeInputAPI> i_nativeInputAPI,
		std::unique_ptr<audios::INativeAudioAPI> i_nativeAudioAPI,
		std::shared_ptr<core::GameSetting> i_gameSetting
	);
	void Initialize();
	bool IsInitialized() const;
	void LoadResource();
	void RunLoop(const core::Duration& dt);
	void Pause();
	void Resume();
	void Shutdown();

	signals::Signal<> sig_requestShutdown;
private:
	void UpdateInput(const const core::Duration& dt);

	void FixedUpdate(const const core::Duration& dt);
	void PreFixedUpdate(const const core::Duration& dt);
	void DuringFixedUpdate(const const core::Duration& dt);
	void PostFixedUpdate(const const core::Duration& dt);

	void Update(const const core::Duration& dt);
	void PreUpdate(const const core::Duration& dt);
	void DuringUpdate(const const core::Duration& dt);
	void PostUpdate(const const core::Duration& dt);

	void Render(const const core::Duration& dt);
	void PreRender(const const core::Duration& dt);
	void DuringRender(const const core::Duration& dt);
	void PostRender(const const core::Duration& dt);

	void OnRequestShutdown();

	// own, self init
	std::shared_ptr<GameClock> m_gameClock;
	std::shared_ptr<files::IFileSystem> m_fileSystem;
	std::shared_ptr<graphics::IGraphicSystem> m_graphicSystem;
	std::shared_ptr<physics::IPhysicSystem> m_physicSystem;
	std::shared_ptr<inputs::IInputSystem> m_inputSystem;
	std::shared_ptr<audios::IAudioSystem> m_audioSystem;
	std::shared_ptr<camera::ICameraSystem> m_cameraSystem;
	std::shared_ptr<core::GameSetting> m_gameSetting;
	std::shared_ptr<database::IDatabase> m_database;
	std::shared_ptr<IComponentFactory> m_componentFactory;
	std::shared_ptr<IEntityFactory> m_entityFactory;
	std::shared_ptr<IScriptContext> m_scriptContext;

	// own, pass by param
	std::unique_ptr<graphics::INativeGraphicAPI> m_nativeGraphicAPI;
	std::unique_ptr<inputs::INativeInputAPI> m_nativeInputAPI;
	std::unique_ptr<audios::INativeAudioAPI> m_nativeAudioAPI;

	// game clock relate
	core::Duration m_perFrameDuration = 0;
	core::Duration m_lastFixedUpdateDuration = 0;
	bool m_waitForFixedUpdate = false;

	// others
	bool m_isInitialized = false;
	bool m_isPaused = false;

	// test
	std::unique_ptr<Script> m_wormScript;
};

} // namespace logic