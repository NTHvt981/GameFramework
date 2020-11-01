#pragma once

#include "../../Entity.h"
#include "../../Physic.h"
#include "../../../Constraints.h"
#include "../../../Camera/Camera.h"
#include "../../../Input/Input.h"
#include "../../../Unit/Animation.h"

#define DOME_UP_MOVE_LEFT 1
#define DOME_UP_MOVE_RIGHT 2
#define DOME_DOWN_MOVE_LEFT 3
#define DOME_DOWN_MOVE_RIGHT 4
#define DOME_LEFT_MOVE_UP 5
#define DOME_LEFT_MOVE_DOWN 6
#define DOME_RIGHT_MOVE_UP 7
#define DOME_RIGHT_MOVE_DOWN 8

#define DOME_CLING 0
#define DOME_FLY 1

class CDome : public CEntity
{
private:
	float speed = 0.5;

	Vector old_velocity;

	LPAnimation domeUpMoveLeft;
	LPAnimation domeUpMoveRight;

	LPAnimation domeLeftMoveUp;
	LPAnimation domeLeftMoveDown;

	LPAnimation domeRightMoveUp;
	LPAnimation domeRightMoveDown;

	LPAnimation domeDownMoveLeft;
	LPAnimation domeDownMoveRight;

	int facialState = DOME_UP_MOVE_LEFT;
	int flyingState = DOME_CLING;

private:
	void SetState();
	void GetState(DWORD dt);
	void MoveLeft(DWORD dt);
	void MoveRight(DWORD dt);
	void MoveUp(DWORD dt);
	void MoveDown(DWORD dt);
	void Fly(DWORD dt);
	void DontMove(DWORD dt);

public:
	CDome();
	void Update(DWORD dt);
	void Render();
};