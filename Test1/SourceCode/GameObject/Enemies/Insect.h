#pragma once

#include "../Enemies/Enemy.h"
#include "../Physic.h"
#include "../../Constraints.h"
#include "../../Unit/Animation.h"

#define INSECT_DRIFT_DOWN 1
#define INSECT_BOOST_UP 2

#define INSECT_NORMAL 1
#define INSECT_SHOOT_PLAYER 1

#define INSECT_RANGE 150
#define INSECT_BULLET_SPEED 3

class CInsect : public CEnemy
{
private:
	const DWORD driftDownTime = 150;
	const DWORD boostUpTime = 50;
	DWORD stateTime = 0;

	DWORD shootCountUp = 0;
	DWORD shootWaitTime = 150;

	const float driftDownSpeed = 0.75;
	const float boostUpSpeed = 2.25;

	int state = INSECT_DRIFT_DOWN;

	LPAnimation leftAni;
	LPAnimation rightAni;
	LPAnimation animation;

private:
	void DriftDownState(DWORD dt);
	void BoostUpState(DWORD dt);
	void HandleShoot(DWORD dt);

public:
	CInsect();
	void Update(DWORD dt);
	void Render();
};

