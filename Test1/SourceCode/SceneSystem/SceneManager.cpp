#include "SceneManager.h"

void CSceneManager::Init()
{
	introScene = new CIntroScene();
	sideScrollScene = new CSideScrollScene();
	topDownScene = new CTopDownScene();
	gameOverScene = new CGameOverScene();
	bossScene = new CBossScene();
	endingScene = new CEndingScene;

	currentScene = sideScrollScene;
}

void CSceneManager::LoadResources()
{
	transScreen = CSpriteLibrary::GetInstance()->Get(ID_BLACK_SCREEN);

	sideScrollScene->LoadResources();
	topDownScene->LoadResources();
	bossScene->LoadResources();
	introScene->LoadResources();
	endingScene->LoadResources();

	//introScene->Start();
	//endingScene->Start();

	sideScrollScene->Start(
		INTRO_TO_SIDESCROLL_POS.x, 
		INTRO_TO_SIDESCROLL_POS.y
	);
	restartPosition.Set(INTRO_TO_SIDESCROLL_POS.x, INTRO_TO_SIDESCROLL_POS.y);

	//topDownScene->Start(
	//	SIDESCROLL_TO_TOPDOWN_POS.x,
	//	SIDESCROLL_TO_TOPDOWN_POS.y
	//);
	//restartPosition.Set(SIDESCROLL_TO_TOPDOWN_POS.x, SIDESCROLL_TO_TOPDOWN_POS.y);

	//bossScene->Start();
}

void CSceneManager::Update(DWORD dt)
{
	switch (mode)
	{
	case NORMAL_MODE:
		NormalMode(dt);
		break;
	case BEGIN_CHANGESCENE_MODE:
		BeginChangeSceneMode(dt);
		break;
	case DURING_CHANGESCENE_MODE:
		DuringChangeSceneMode(dt);
		break;
	case END_CHANGESCENE_MODE:
		EndChangeSceneMode(dt);
		break;
	case BEGIN_RESTART_MODE:
		BeginRestartMode(dt);
		break;
	case DURING_RESTART_MODE:
		DuringRestartMode(dt);
		break;
	case END_RESTART_MODE:
		EndRestartMode(dt);
		break;
	default:
		break;
	}
	//currentScene->Update(dt);
}

void CSceneManager::Render()
{
	currentScene->Render();

	if (mode != NORMAL_MODE)
		transScreen->DrawWithFixedPosition(
			0, 0, transAlpha
		);
	else
		ExecuteRequests();
}

void CSceneManager::ExecuteRequests()
{
	list<LPGameRequest> requests = CGameRequest::RequestList;

	while (!requests.empty())
	{
		LPGameRequest re = requests.front();

		ExecuteRequest(re);
		requests.pop_front();
	}

	CGameRequest::RequestList.clear();
}

void CSceneManager::ExecuteRequest(LPGameRequest request)
{
	switch (request->Type)
	{
	case GAME_REQUEST_TYPES::SwitchToEnding:
		break;
	case GAME_REQUEST_TYPES::SwitchToIntro:
		break;
	case GAME_REQUEST_TYPES::SwitchToSideScroll:
		nextScene = sideScrollScene;
		mode = BEGIN_CHANGESCENE_MODE;
		break;
	case GAME_REQUEST_TYPES::SwitchToTopDown:
		nextScene = topDownScene;
		mode = BEGIN_CHANGESCENE_MODE;
		break;
	default:
		break;
	}
}

void CSceneManager::NormalMode(DWORD dt)
{
	currentScene->Update(dt);

	if (CPlayerHealth::GetInstance()->IsGameOver())
	{
		CPlayer::GetCurrentPlayer()->Disable();
		mode = BEGIN_RESTART_MODE;
	}

	transAlpha = 0;
}

void CSceneManager::BeginChangeSceneMode(DWORD dt)
{
	transAlpha = min(transAlpha + transAlphaDivient, 1);
	if (transAlpha == 1)
		mode = DURING_CHANGESCENE_MODE;
}

void CSceneManager::DuringChangeSceneMode(DWORD dt)
{
	switch (nextScene->Type)
	{
	case SCENE_TYPES::SideScrollScene:
		if (currentScene->Type == SCENE_TYPES::IntroScene)
		{
			sideScrollScene->Start(
				INTRO_TO_SIDESCROLL_POS.x,
				INTRO_TO_SIDESCROLL_POS.y
			);
			restartPosition.Set(INTRO_TO_SIDESCROLL_POS.x, INTRO_TO_SIDESCROLL_POS.y);
		}
		else if (currentScene->Type == SCENE_TYPES::TopDownScene)
		{
			sideScrollScene->Resume();
			restartPosition.Set(
				CPlayer::GetCurrentPlayer()->GetPosition().x, 
				CPlayer::GetCurrentPlayer()->GetPosition().y
			);

			CPlayer::SetCurrentPlayer(CJason::GetInstance());
		}
		break;

	case SCENE_TYPES::TopDownScene:
		topDownScene->Start(
			SIDESCROLL_TO_TOPDOWN_POS.x,
			SIDESCROLL_TO_TOPDOWN_POS.y
		);
		restartPosition.Set(SIDESCROLL_TO_TOPDOWN_POS.x, SIDESCROLL_TO_TOPDOWN_POS.y);
		break;

	case SCENE_TYPES::EndingScene:
		endingScene->Start();
		break;
	}

	currentScene = nextScene;
	nextScene = NULL;

	currentScene->Update(dt);
	mode = END_CHANGESCENE_MODE;
}

void CSceneManager::EndChangeSceneMode(DWORD dt)
{
	transAlpha = max(transAlpha - transAlphaDivient, 0);
	if (transAlpha == 0)
		mode = NORMAL_MODE;
}

void CSceneManager::BeginRestartMode(DWORD dt)
{
	transAlpha = min(transAlpha + transAlphaDivient, 1);
	if (transAlpha == 1)
		mode = DURING_RESTART_MODE;
}

void CSceneManager::DuringRestartMode(DWORD dt)
{
	switch (currentScene->Type)
	{
	case SCENE_TYPES::SideScrollScene:
		sideScrollScene->ReStart(restartPosition.x, restartPosition.y);
		break;

	case SCENE_TYPES::TopDownScene:
		topDownScene->Start(restartPosition.x, restartPosition.y);
		break;
	}

	CPlayerHealth::GetInstance()->Restart();
	
	currentScene->Update(dt);
	mode = END_RESTART_MODE;
}

void CSceneManager::EndRestartMode(DWORD dt)
{
	transAlpha = max(transAlpha - transAlphaDivient, 0);
	if (transAlpha == 0)
	{
		CPlayer::GetCurrentPlayer()->Enable();
		mode = NORMAL_MODE;
	}
}
