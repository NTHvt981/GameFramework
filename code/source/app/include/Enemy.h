#pragma once

#include "Entity.h"
#include "Constraints.h"
#include "SceneRequest.h"
#include "Player.h"
#include "Utils.h"
#include "Explosion.h"
#include "EnemyBullet.h"
#include "SoundLibrary.h"

enum ENEMY_TYPE {
	Canon,
	Dasher,
	Dome,
	EyeBall,
	Floater,
	Head,
	Insect,
	Jumper,
	Orb,
	Skull,
	Spiral,
	Teleporter,
	Walker,
	Worm
};

#define HEALTH_PICKUP_CHANCE 0.5

//#define SPIRAL_HEALTH 10

class CEnemy : public CEntity
{
protected:
	int64_t maxHealth;
	int64_t health;
	Vector old_velocity;

	int64_t width;
	int64_t height;

public:
	CEnemy();

	virtual void Update(DWORD dt);

	virtual void InflictDamage(int64_t dam);
	CEnemy* SetMaxHealth(int64_t mh);

	float DistanceToPlayer();
	float HorizontalDistanceToPlayer();
	float VerticalDistanceToPlayer();

	bool InPlayerZone();
};

