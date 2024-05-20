#pragma once
#include "IScene.h"
#include "Logic/Scripts/ScriptsManager.h"
#include "Logic/Mailbox/IMailboxSender.h"
#include "Logic/Components/IComponentsFactory.h"
#include "Logic/Scripts/ScriptContext.h"
#include "Logic/GameClock.h"
#include "Logic/Entities/EntitiesManager.h"
#include <memory>

namespace logic
{

class IntroScene: public IScene
{
public:
	IntroScene(std::shared_ptr<GameClock> i_gameClock,
		std::shared_ptr<IEntitiesFactory> i_entitiesFactory,
		std::shared_ptr<IMailboxSender> i_mailboxSendToGame);
	~IntroScene();

	void PreFixedUpdate(const core::Duration& dt) override;
	void DuringFixedUpdate(const core::Duration& dt) override;
	void PostFixedUpdate(const core::Duration& dt) override;

	void PreUpdate(const core::Duration& dt) override;
	void DuringUpdate(const core::Duration& dt) override;
	void PostUpdate(const core::Duration& dt) override;

	void PreRender(const core::Duration& dt) override;
	void DuringRender(const core::Duration& dt) override;
	void PostRender(const core::Duration& dt) override;

	void OnDestroy() override;

private:
	void OnIntroFinished();

	std::shared_ptr<ScriptsManager> m_scriptsManager;
	std::shared_ptr<IMailboxSender> m_mailboxSendToGame;
	std::shared_ptr<EntitiesManager> m_entitiesManager;
	std::shared_ptr<IScriptContext> m_scriptContext;

	signals::Connection<> m_introFinishedCon;
};

} // namespace logic