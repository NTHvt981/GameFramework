#pragma once
#include "GameClock.h"
#include "PhysicSystem/IPhysicSystem.h"
#include "FileSystem/IFileSystem.h"
#include "Database/IDatabase.h"
#include "Logic/LogicSystems/CameraSystem/ICameraSystem.h"
#include "Logic/Scripts/Script.h"
#include <memory>

namespace graphics
{
class INativeGraphicAPI;
class IGraphicSystem;
} // namespace graphics

namespace inputs
{
class INativeInputAPI;
class IInputSystem;
} // namespace inputs

namespace audios
{
class INativeAudioAPI;
class IAudioSystem;
} // namespace audios

namespace core
{
class GameSetting;
} // namespace core

namespace logic
{

class IScriptContext;
class IComponentsFactory;
class IEntitiesFactory;
class EntitiesManager;
class ScriptsManager;
namespace camera
{
class ICameraSystem;
} // namespace camera

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
	void UpdateInput(const core::Duration& dt);

	void FixedUpdate(const core::Duration& dt);
	void PreFixedUpdate(const core::Duration& dt);
	void DuringFixedUpdate(const core::Duration& dt);
	void PostFixedUpdate(const core::Duration& dt);

	void Update(const core::Duration& dt);
	void PreUpdate(const core::Duration& dt);
	void DuringUpdate(const core::Duration& dt);
	void PostUpdate(const core::Duration& dt);

	void Render(const core::Duration& dt);
	void PreRender(const core::Duration& dt);
	void DuringRender(const core::Duration& dt);
	void PostRender(const core::Duration& dt);

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
	std::shared_ptr<IComponentsFactory> m_componentFactory;
	std::shared_ptr<IEntitiesFactory> m_entitiesFactory;
	std::shared_ptr<EntitiesManager> m_entitiesManager;
	std::shared_ptr<IScriptContext> m_scriptContext;
	std::shared_ptr<ScriptsManager> m_scriptsManager;

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