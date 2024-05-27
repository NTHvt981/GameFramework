#pragma once
#include "GameClock.h"
#include "Logic/LogicSystems/PhysicSystem.h"
#include "Logic/LogicSystems/IFileSystem.h"
#include "Logic/Databases/IDatabase.h"
#include "Logic/LogicSystems/CameraSystem/ICameraSystem.h"
#include "Logic/Scripts/Script.h"
#include "Mailbox/Mailbox.h"
#include "Scenes/IScene.h"
#include <memory>
#include <queue>

namespace logic
{
class IInputSystem;
} // namespace logic

namespace audios
{
class INativeAudioAPI;
class IAudioSystem;
} // namespace audios

namespace core
{
class GameSetting;
class INativeGraphicAPI;
class INativeInputAPI;
} // namespace core

namespace logic
{
class IGraphicSystem;
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
		std::unique_ptr<core::INativeGraphicAPI> i_nativeGraphicAPI,
		std::unique_ptr<core::INativeInputAPI> i_nativeInputAPI,
		std::unique_ptr<audios::INativeAudioAPI> i_nativeAudioAPI,
		std::shared_ptr<core::GameSetting> i_gameSetting
	);
	void Initialize();
	bool IsInitialized() const;
	void LoadResource();
	using EndLoop = bool;
	EndLoop RunLoop(const core::Duration& dt);
	void Pause();
	void Resume();
	void Shutdown();
	void OnResizeWindow(const core::SizeUI64& i_size);
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

	void ProcessMailbox();

	// own, self init
	std::shared_ptr<GameClock> m_gameClock;
	std::shared_ptr<IFileSystem > m_fileSystem;
	std::shared_ptr<IGraphicSystem> m_graphicSystem;
	std::shared_ptr<PhysicSystem> m_physicSystem;
	std::shared_ptr<IInputSystem> m_inputSystem;
	std::shared_ptr<audios::IAudioSystem> m_audioSystem;
	std::shared_ptr<logic::camera::ICameraSystem> m_cameraSystem;
	std::shared_ptr<core::GameSetting> m_gameSetting;
	std::shared_ptr<IDatabase> m_database;
	std::shared_ptr<IComponentsFactory> m_componentFactory;
	std::shared_ptr<IEntitiesFactory> m_entitiesFactory;

	// scenes
	std::queue<std::shared_ptr<IScene>> m_scenes;
	std::shared_ptr<Mailbox> m_mailboxReceiveFromScene;

	// own, pass by param
	std::unique_ptr<core::INativeGraphicAPI> m_nativeGraphicAPI;
	std::unique_ptr<core::INativeInputAPI> m_nativeInputAPI;
	std::unique_ptr<audios::INativeAudioAPI> m_nativeAudioAPI;

	// game clock relate
	core::Duration m_perFrameDuration = 0;
	core::Duration m_lastFixedUpdateDuration = 0;
	bool m_waitForFixedUpdate = false;

	// others
	bool m_isInitialized = false;
	bool m_isPaused = false;
};

} // namespace logic