#pragma once

#include "../Constraints.h"
#include "../Unit/Sprite.h"
#include "../Library/SpriteLibrary.h"

#include "IntroScene.h"
#include "EndingScene.h"
#include "GameOverScene.h"
#include "SideScrollScene.h"
#include "TopDownScene.h"

#define NORMAL_MODE 0
#define BEGIN_CHANGESCENE_MODE 1
#define DURING_CHANGESCENE_MODE 2
#define END_CHANGESCENE_MODE 3

class CSceneManager
{
private:
	CScene* currentScene = NULL;
	CScene* nextScene = NULL;

	CIntroScene *introScene;
	CSideScrollScene *sideScrollScene;
	CTopDownScene *topDownScene;
	CGameOverScene *gameOverScene;

	int mode = NORMAL_MODE;

	LPSprite transScreen = NULL;
	float transAlpha = 0;
	float transAlphaDivient = 0.05;

public:
	void Init();
	void LoadResources();
	void Update(DWORD dt);
	void Render();

private:
	void ExecuteRequests();
	void ExecuteRequest(LPGameRequest request);

private:
	void NormalMode(DWORD dt);
	void BeginChangeSceneMode(DWORD dt);
	void DuringChangeSceneMode(DWORD dt);
	void EndChangeSceneMode(DWORD dt);
};

