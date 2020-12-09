#pragma once

#include "../Constraints.h"
#include "Scene.h"

#include "../Player/JasonTopDown.h"

#include "../Game/GameRequest.h"
#include "../GameObject/Boss/Boss.h"

class CBossScene: public CScene
{
protected:
	CJasonTopDown* player;
	CBoss* boss;

	bool gameOver = false;

	DWORD waitTime;
	const DWORD afterDefeatingBossTime = 300;

	const float width = CAMERA_WIDTH;
	const float height = CAMERA_HEIGHT;

public:
	CBossScene();

	void Start();
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void End();
};

