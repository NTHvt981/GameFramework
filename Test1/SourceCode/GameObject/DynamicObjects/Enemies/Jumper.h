#pragma once

#include "../../Entity.h"
#include "../../Physic.h"
#include "../../../Constraints.h"
#include "../../../Unit/Animation.h"

#define JUMPER_MOVE_LEFT -1
#define JUMPER_DONT_MOVE 0
#define JUMPER_MOVE_RIGHT 1

#define JUMPER_ON_GROUND 0
#define JUMPER_ON_AIR 1

class CJumper: public CEntity
{
private:
	float speed = 0.4;

	Vector old_velocity;

	LPAnimation moveLeftAni;
	LPAnimation moveRightAni;

	int horizontalState = JUMPER_DONT_MOVE;
	int verticalState = JUMPER_ON_GROUND;

private:
	void SetState();
	void GetState(DWORD dt);
	void MoveLeft(DWORD dt);
	void MoveRight(DWORD dt);
	void DontMove(DWORD dt);

public:
	CJumper();
	void Update(DWORD dt);
	void Render();
};

