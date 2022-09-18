#pragma once

#include "Constraints.h"
#include "Sprite.h"
#include "SpriteLibrary.h"

#include "SoundLibrary.h"

#include "IntroScene.h"
#include "EndingScene.h"
#include "SideScrollScene.h"
#include "TopDownScene.h"
#include "BossScene.h"

#define NORMAL_MODE 0
#define BEGIN_CHANGESCENE_MODE 1
#define DURING_CHANGESCENE_MODE 2
#define END_CHANGESCENE_MODE 3

#define BEGIN_RESTART_MODE 4
#define DURING_RESTART_MODE 5
#define END_RESTART_MODE 6

class CSceneManager
{
private:
	CScene* currentScene = NULL;
	CScene* nextScene = NULL;

	CIntroScene *introScene;
	CSideScrollScene *sideScrollScene;
	CTopDownScene *topDownScene;
	CEndingScene* endingScene;
	CBossScene* bossScene;

	int64_t mode = NORMAL_MODE;

	LPSprite transScreen = NULL;
	float transAlpha = 0;
	float transAlphaDivient = 0.05;

	Vector restartPosition = Vector(0, 0);

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

	void BeginRestartMode(DWORD dt);
	void DuringRestartMode(DWORD dt);
	void EndRestartMode(DWORD dt);
};

