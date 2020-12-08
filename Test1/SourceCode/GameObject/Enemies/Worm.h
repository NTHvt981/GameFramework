#pragma once

#include "../Enemies/Enemy.h"
#include "../Physic.h"
#include "../../Constraints.h"
#include "../../Unit/Animation.h"

#define WORM_NORMAL 1
#define WORM_CHASE_PLAYER 2

#define WORM_LEFT -1
#define WORM_RIGHT 1

class CWorm : public CEnemy
{
private:
	const float normalSpeed = 0.4;
	const float chaseSpeed = 0.8;
	const float gravity = 0.25;
	const float jumpSpeed = 4;

	LPAnimation moveLeftAni;
	LPAnimation moveRightAni;
	LPAnimation animation;

	int state = WORM_NORMAL;
	int facing = WORM_RIGHT;

	const float innerRadius = 50;
	const float outerRadius = 75;
	const float chaseLimit = 10;

private:
	void NormalState(DWORD dt);
	void ChasePlayerState(DWORD dt);

public:
	CWorm();
	void Update(DWORD dt);
	void Render();
};

