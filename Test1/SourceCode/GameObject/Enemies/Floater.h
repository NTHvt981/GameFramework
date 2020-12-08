#pragma once

#include "../Enemies/Enemy.h"
#include "../Physic.h"
#include "../../Constraints.h"
#include "../../Unit/Animation.h"

#define FLOATER_LEFT -1
#define FLOATER_RIGHT 1
#define FLOATER_UP -1
#define FLOATER_DOWN 1

#define FLOATER_DIAGONAL 1
#define FLOATER_HORIZONTAL 2
#define FLOATER_VERTICAL 3

class CFloater : public CEnemy
{
private:
	const float diagonalSpeed = 1;
	const float horizontalSpeed = 1.4;
	const float verticalSpeed = 1.2;

	LPAnimation animation;

	int horFacing = FLOATER_RIGHT;
	int verFacing = FLOATER_DOWN;
	int floaterType = FLOATER_DIAGONAL;

private:
	void FloatDiagonal(DWORD dt);
	void FloatHorizontal(DWORD dt);
	void FloatVertical(DWORD dt);

public:
	CFloater(int _type = FLOATER_DIAGONAL);
	void Update(DWORD dt);
	void Render();
};

