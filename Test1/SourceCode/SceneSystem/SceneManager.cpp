#include "SceneManager.h"

void CSceneManager::Init()
{
	introScene = new CIntroScene();
	sideScrollScene = new CSideScrollScene();
	topDownScene = new CTopDownScene();
	gameOverScene = new CGameOverScene();
	bossScene = new CBossScene();

	currentScene = bossScene;
}

void CSceneManager::LoadResources()
{
	transScreen = CSpriteLibrary::GetInstance()->Get(ID_BLACK_SCREEN);

	sideScrollScene->LoadResources();
	topDownScene->LoadResources();
	bossScene->LoadResources();

	//sideScrollScene->Start(
	//	TOPDOWN_TO_SIDESCROLL_POS.x, 
	//	TOPDOWN_TO_SIDESCROLL_POS.y
	//);

	//topDownScene->Start(
	//	SIDESCROLL_TO_TOPDOWN_POS.x,
	//	SIDESCROLL_TO_TOPDOWN_POS.y
	//);

	bossScene->Start();
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
		}
		else if (currentScene->Type == SCENE_TYPES::TopDownScene)
		{
			sideScrollScene->Resume();

			CPlayer::SetCurrentPlayer(CJason::GetInstance());
		}
		break;

	case SCENE_TYPES::TopDownScene:
		topDownScene->Start(
			SIDESCROLL_TO_TOPDOWN_POS.x,
			SIDESCROLL_TO_TOPDOWN_POS.y
		);
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
