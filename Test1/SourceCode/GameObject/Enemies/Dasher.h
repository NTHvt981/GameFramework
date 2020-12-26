#pragma once

#include "Enemy.h"
#include "../../Constraints.h"
#include "../../Unit/Animation.h"

#include "../../Debug/Utils.h"

#define DASHER_HORIZONTAL 0
#define DASHER_VERTICAL 1

#define DASHER_IDLE 0
#define DASHER_MOVE 1

#define DASHER_SPEED 4

class CDasher : public CEnemy
{
private:
	int type;
	float speed = DASHER_SPEED;
	LPAnimation animation;
	LPAnimation idleAni;
	LPAnimation moveAni;

	const float maxRange = 8;

private:
	void IdleState(DWORD dt);
	void MoveState(DWORD dt);

public:
	CDasher(int _type = DASHER_VERTICAL);
	void Update(DWORD dt);
	void Render();
};

