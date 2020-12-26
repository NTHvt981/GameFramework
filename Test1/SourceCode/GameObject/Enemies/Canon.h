#pragma once

#include "Enemy.h"
#include "../../Constraints.h"
#include "../../Unit/Animation.h"

#include "../../Debug/Utils.h"

#include "../EnemyBullets/EnemyBullet.h"

#define CANON_BULLET_SPEED 3

class CCanon : public CEnemy
{
private:
	LPAnimation animation;

	int currFrame = 0;
	int prevFrame = 0;

private:
	const int span = 12;

	void ShootHorizontal(DWORD dt);
	void ShootVertical(DWORD dt);

public:
	CCanon();
	void Update(DWORD dt);
	void Render();
};

