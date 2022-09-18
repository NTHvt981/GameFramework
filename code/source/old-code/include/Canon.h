#pragma once

#include "Enemy.h"
#include "Constraints.h"
#include "Animation.h"

#include "Utils.h"

#include "EnemyBullet.h"

#define CANON_BULLET_SPEED 3

class CCanon : public CEnemy
{
private:
	LPAnimation animation;

	int64_t currFrame = 0;
	int64_t prevFrame = 0;

private:
	const int64_t span = 12;

	void ShootHorizontal(DWORD dt);
	void ShootVertical(DWORD dt);

public:
	CCanon();
	void Update(DWORD dt);
	void Render();
};

