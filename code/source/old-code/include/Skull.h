#pragma once

#include "Enemy.h"
#include "Physic.h"
#include "Constraints.h"
#include "Animation.h"

#include "EnemyBullet.h"

#define SKULL_NORMAL 1
#define SKULL_FLY_ABOVE 2
#define SKULL_DROP_BOMB 3
#define SKULL_FLY_BELOW 4

#define SKULL_LEFT -1
#define SKULL_RIGHT 1

class CSkull : public CEnemy
{
private:
	const float horizontalSpeed = 2;
	const float verticalSpeed = 3;

	float distanceTravel = 0;

	int64_t facing = SKULL_RIGHT;
	int64_t state = SKULL_NORMAL;

	const float maxDistanceTravel = 20;
	const float horizontalRadius = 25;
	const float verticalRadius = 150;

	LPAnimation moveLeftAni;
	LPAnimation moveRightAni;
	LPAnimation animation;

private:
	void NormalState(DWORD dt);
	void FlyAboveState(DWORD dt);
	void DropBombState(DWORD dt);
	void FlyBelowState(DWORD dt);

public:
	CSkull();
	void Update(DWORD dt);
	void Render();
};

