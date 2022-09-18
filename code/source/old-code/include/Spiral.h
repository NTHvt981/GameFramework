#pragma once

#include "Enemy.h"
#include "Animation.h"

#include "SpiralBullet.h"

class CSpiral : public CEnemy
{
private:
	LPAnimation animation;
	bool isHurt = false;
	const int64_t range = 5;

	const DWORD shootWaitTime = 150;
	DWORD shootCountUp = shootWaitTime;

private:
	void Shoot();

public:
	CSpiral();
	void Update(DWORD dt);
	void Render();

	void InflictDamage(int64_t dam);
};

