#pragma once

#include "../Enemies/Enemy.h"
#include "../Physic.h"
#include "../../Constraints.h"
#include "../../Unit/Animation.h"

#define MY_DOME_CLING 0
#define MY_DOME_FLY 1

class CDome : public CEnemy
{
private:
	const float clingSpeed = 1;
	const float flySpeed = 4;

	const float maxMainAxisDistance = 200;
	const float maxSideAxisDistance = 5;

	LPAnimation domeUpMoveLeft;
	LPAnimation domeUpMoveRight;

	LPAnimation domeLeftMoveUp;
	LPAnimation domeLeftMoveDown;

	LPAnimation domeRightMoveUp;
	LPAnimation domeRightMoveDown;

	LPAnimation domeDownMoveLeft;
	LPAnimation domeDownMoveRight;

	LPAnimation animation;
	int state = MY_DOME_CLING;

	Vector clingDirection = Vector(0, 1);
	Vector moveDirection = Vector(1, 0);

	bool setInitDirection = false;

	DWORD maxWaitTime = 100;
	DWORD waitTime = 0;

private:
	void ClingState(DWORD dt);
	void FlyState(DWORD dt);
	void SetInitDirection();

public:
	CDome();
	void Update(DWORD dt);
	void Render();
};

