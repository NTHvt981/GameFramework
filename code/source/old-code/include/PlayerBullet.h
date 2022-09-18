#pragma once

#include "Enemy.h"
#include "BreakableWall.h"
#include "Timer.h"
#include "Constraints.h"
#include "Sprite.h"
#include "SpriteLibrary.h"

#include "SceneRequest.h"

#include "Explosion.h"

#define SOPHIA_BULLET_SPEED 5;
#define JASON_BULLET_SPEED 3.5;
#define JASON_TOPDOWN_BULLET_SPEED 8;

class CPlayerBullet: public CEntity
{
protected:
	float speed = SOPHIA_BULLET_SPEED;
	const int64_t damage = 2;
	Vector old_velocity;
	LPSprite sprite;
	CTimer* selfDestructTimer;

	EXPLOSION_TYPES effectType = EXPLOSION_TYPES::Medium;

	int64_t width;
	int64_t height;

public:
	CPlayerBullet(Vector direction);
	void CreateEffect(float vx, float vy);
	
	void Update(DWORD dt);
	void Render();
};

