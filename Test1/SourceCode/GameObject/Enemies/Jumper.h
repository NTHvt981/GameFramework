#pragma once

#include "../Enemies/Enemy.h"
#include "../Physic.h"
#include "../../Constraints.h"
#include "../../Unit/Animation.h"

#define JUMPER_NORMAL 0
#define JUMPER_CHASE_PLAYER 1

#define JUMPER_LEFT -1
#define JUMPER_RIGHT 1

class CJumper: public CEnemy
{
private:
	const float normalSpeed = 0.8;
	const float chaseSpeed = 1.6;

	Vector old_velocity;

	LPAnimation moveLeftAni;
	LPAnimation moveRightAni;
	LPAnimation animation;

	int facing = JUMPER_RIGHT;
	int state = JUMPER_NORMAL;

	const float innerRadius = 75;
	const float outerRadius = 125;

private:
	void NormalState(DWORD dt);
	void ChasePlayerState(DWORD dt);

public:
	CJumper();
	void Update(DWORD dt);
	void Render();
};

