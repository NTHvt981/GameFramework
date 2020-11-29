#pragma once

#include "Enemy.h"
//#include "../Entity.h"
#include "../../Constraints.h"
#include "../../Unit/Animation.h"

#include "../../Game/Game.h"

#define WORM_MOVE_LEFT -1
#define WORM_DONT_MOVE 0
#define WORM_MOVE_RIGHT 1

#define WORM_ON_GROUND 0
#define WORM_ON_AIR 1

class CWorm : public CEnemy
{
private:
	float speed = 0.4;

	Vector old_velocity;

	LPAnimation crawlLeftAni;
	LPAnimation crawlRightAni;

	int state = WORM_DONT_MOVE;
	int verticalState = WORM_ON_GROUND;

protected:
	//this function is only called for debug
	void Move(DWORD dt);

private:
	void SetState();
	void GetState(DWORD dt);
	void MoveLeft(DWORD dt);
	void MoveRight(DWORD dt);
	void DontMove(DWORD dt);

public:
	CWorm();
	void Update(DWORD dt);
	void Render();
};

