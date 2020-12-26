#pragma once

#include "Enemy.h"
#include "../../Constraints.h"
#include "../../Unit/Animation.h"

#include "../../Debug/Utils.h"

#include "../EnemyBullets/EnemyBullet.h"

#define EYEBALL_TYPE_IDLE 0
#define EYEBALL_TYPE_MOVE 1

#define EYEBALL_BULLET_SPEED 2.5
#define EYEBALL_MOVE_SPEED 0.5

class CEyeBall : public CEnemy
{
private:
	int type;
	DWORD shootCountUp = 0;
	DWORD shootWaitTime = 100;
	LPAnimation animation;

	DWORD moveCountUp = 0;
	const DWORD moveWaitTime = 250;

	Vector moveDir;
	float speed = EYEBALL_MOVE_SPEED;

private:
	void MoveRandom(DWORD dt);
	void Shoot(DWORD dt);

public:
	CEyeBall(int _type = EYEBALL_TYPE_IDLE);
	void Update(DWORD dt);
	void Render();
};

