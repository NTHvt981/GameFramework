#pragma once

#include "Enemy.h"
#include "Constraints.h"
#include "Animation.h"

#include "Utils.h"

#define WALKER_MOVE 0
#define WALKER_IDLE 1

#define WALKER_BULLET_SPEED 3
#define WALKER_MOVE_SPEED 0.5

class CWalker : public CEnemy
{
private:
	Vector old_velocity;

	LPAnimation moveDownAni;
	LPAnimation moveUpAni;
	LPAnimation currentAni;

	int64_t state = WALKER_IDLE;
	Vector moveDir;
	const int64_t range = 200;

	DWORD countUp = 0;
	const DWORD stopWaitTime = 50;
	const DWORD moveWaitTime = 150;

	DWORD velocityCountUp = 0;
	const DWORD velocityWaitTime = 300;

	bool stopShoot = false;

private:
	void MoveState(DWORD dt);
	void IdleState(DWORD dt);
	void GetSetAnimation(DWORD dt);

	void MoveRandom(DWORD dt);
	void MoveTowardPlayer(DWORD dt);

public:
	CWalker();
	void Update(DWORD dt);
	void Render();
};

