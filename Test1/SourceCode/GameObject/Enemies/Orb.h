#pragma once

//#include "../Entity.h"
#include "Enemy.h"
#include "../Physic.h"
#include "../../Constraints.h"
#include "../../Unit/Animation.h"
#include "../../Game/GameRequest.h"

#define ORB_MOVE_LEFT 0
#define ORB_TURN_RIGHT 1
#define ORB_TURN_LEFT 2
#define ORB_MOVE_RIGHT 3

class COrb: public CEnemy
{
private:
	float speed = 1;

	Vector old_velocity;

	LPAnimation moveLeftAni;
	LPAnimation moveRightAni;
	LPAnimation turnLeftAni;
	LPAnimation turnRightAni;

	LPAnimation currentAni;

	int state;

private:
	void SetState();
	void GetState(DWORD dt);
	void MoveLeft(DWORD dt);
	void MoveRight(DWORD dt);
	void TurnLeft(DWORD dt);
	void TurnRight(DWORD dt);

public:
	COrb();
	void Update(DWORD dt);
	void Render();
};

