#pragma once

#include "../GameObject/Enemies/Enemy.h"
#include "../GameObject/StaticObjects/BreakableWall.h"
#include "../Timer/Timer.h"
#include "../Constraints.h"
#include "../Unit/Sprite.h"
#include "../Library/SpriteLibrary.h"

#include "../SceneSystem/SceneRequest.h"

#include "../GameObject/StaticObjects/Explosion.h"

#define SOPHIA_BULLET_SPEED 5;
#define JASON_BULLET_SPEED 3.5;
#define JASON_TOPDOWN_BULLET_SPEED 8;

class CPlayerBullet: public CEntity
{
protected:
	float speed = SOPHIA_BULLET_SPEED;
	const int damage = 2;
	Vector old_velocity;
	LPSprite sprite;
	CTimer* selfDestructTimer;

	EXPLOSION_TYPES effectType = EXPLOSION_TYPES::Medium;

	int width;
	int height;

public:
	CPlayerBullet(Vector direction);
	void CreateEffect(float vx, float vy);
	
	void Update(DWORD dt);
	void Render();
};

