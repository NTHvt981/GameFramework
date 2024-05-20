#include "Logic/Scenes/IntroScene.h"
#include "Logic/Components/ComponentsFactory.h"
#include "Scripts/IntroScript.h"
#include "Logic/Mailbox/Mail.h"

namespace logic
{

IntroScene::IntroScene(std::shared_ptr<GameClock> i_gameClock,
	std::shared_ptr<IEntitiesFactory> i_entitiesFactory,
	std::shared_ptr<IMailboxSender> i_mailboxSendToGame)
	: m_mailboxSendToGame(i_mailboxSendToGame)
{
	m_entitiesManager = std::make_shared<EntitiesManager>();
	m_scriptContext = std::make_shared<ScriptContext>(
		core::Ref<core::logic::IGameClock>(i_gameClock),
		core::Ref<IEntitiesFactory>(i_entitiesFactory),
		core::Ref<EntitiesManager>(m_entitiesManager)
	);
	m_scriptsManager = std::make_shared<ScriptsManager>(m_scriptContext);

	std::unique_ptr<IntroScript> introScript = std::make_unique<IntroScript>();
	m_introFinishedCon = introScript->sig_onIntroFinished.Connect(
		std::bind(&IntroScene::OnIntroFinished, this)
	);
	m_scriptsManager->AddScript(std::move(introScript));
}

IntroScene::~IntroScene()
{
}

void IntroScene::PreFixedUpdate(const core::Duration& dt)
{
	m_scriptsManager->OnPreFixedUpdate(dt);
}

void IntroScene::DuringFixedUpdate(const core::Duration& dt)
{
	m_scriptsManager->OnFixedUpdate(dt);
}

void IntroScene::PostFixedUpdate(const core::Duration& dt)
{
	m_scriptsManager->OnPostFixedUpdate(dt);
}

void IntroScene::PreUpdate(const core::Duration& dt)
{
	m_scriptsManager->OnPreUpdate(dt);
}

void IntroScene::DuringUpdate(const core::Duration& dt)
{
	m_scriptsManager->OnUpdate(dt);
}

void IntroScene::PostUpdate(const core::Duration& dt)
{
	m_scriptsManager->OnPostUpdate(dt);
}

void IntroScene::PreRender(const core::Duration& dt)
{
	m_scriptsManager->OnPreRender(dt);
}

void IntroScene::DuringRender(const core::Duration& dt)
{
	m_scriptsManager->OnRender(dt);
}

void IntroScene::PostRender(const core::Duration& dt)
{
	m_scriptsManager->OnPostRender(dt);
}

void IntroScene::OnDestroy()
{
	m_introFinishedCon.Disconnect();
}

void IntroScene::OnIntroFinished()
{
	m_mailboxSendToGame->Send(std::make_shared<Mail>(PopSceneMail()));
}

} // namespace logic