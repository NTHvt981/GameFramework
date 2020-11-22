#pragma once

#include "../Entity.h"
#include "../Physic.h"
#include "../../Constraints.h"
#include "../../Unit/Animation.h"

#define WALKER_MOVE_UP -1
#define WALKER_DONT_MOVE 0
#define WALKER_MOVE_DOWN 1

class CWalker : public CEntity
{
private:
	float speed = 0.4;

	Vector old_velocity;

	LPAnimation moveDownAni;
	LPAnimation moveUpAni;
	LPAnimation currentAni;

	int verticalState = WALKER_MOVE_DOWN;

private:
	void SetState();
	void GetState(DWORD dt);
	void MoveDown(DWORD dt);
	void MoveUp(DWORD dt);
	void DontMove(DWORD dt);

public:
	CWalker();
	void Update(DWORD dt);
	void Render();
};

