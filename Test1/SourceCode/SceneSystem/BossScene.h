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

	const float width = CAMERA_WIDTH;
	const float height = CAMERA_HEIGHT;

	long countId = 0;
	
	DWORD winCountUp = 0;
	const DWORD winWaitTime = 300;
	int state = BOSS_NORMAL;

private:
	void ExecuteRequests();
	void ExecuteRequest(LPSceneRequest request);

	//set new entity pos, add it to entity map, set what grid it is in
	void AddEntity(LPEntity entity, float x, float y);
	void RemoveEntity(int id);

	void UpdateOtherEntities(DWORD dt);
	void RenderOtherEntities();

	void ResetEntityCoCollisionBoxes(LPEntity entity);

	void NormalState(DWORD dt);
	void DefeatState(DWORD dt);

public:
	CBossScene();

	void Start(float x, float y);
	void ReStart(float x, float y);
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void End();
};

