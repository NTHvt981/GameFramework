#pragma once

#include "../../Entity.h"
#include "../../Physic.h"
#include "../../../Constraints.h"
#include "../../../Unit/Animation.h"

#define WORM_MOVE_LEFT -1
#define WORM_DONT_MOVE 0
#define WORM_MOVE_RIGHT 1

#define WORM_ON_GROUND 0
#define WORM_ON_AIR 1

class CWorm : public CEntity, public IPhysic
{
private:
	float speed = 0.4;

	Vector old_velocity;

	LPAnimation crawlLeftAni;
	LPAnimation crawlRightAni;

	int horizontalState = WORM_DONT_MOVE;
	int verticalState = WORM_ON_GROUND;

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

