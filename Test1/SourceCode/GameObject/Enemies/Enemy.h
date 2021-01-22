#pragma once

#include "../Entity.h"
#include "../../Constraints.h"
#include "../../SceneSystem/SceneRequest.h"

#include "../../Player/Player.h"

#include "../../Debug/Utils.h"

#include "../StaticObjects/Explosion.h"

#include "../EnemyBullets/EnemyBullet.h"

#include "../../GraphicAndSound/SoundLibrary.h"

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
	int maxHealth;
	int health;
	Vector old_velocity;

	int width;
	int height;

public:
	CEnemy();

	virtual void Update(DWORD dt);

	virtual void InflictDamage(int dam);
	CEnemy* SetMaxHealth(int mh);

	float DistanceToPlayer();
	float HorizontalDistanceToPlayer();
	float VerticalDistanceToPlayer();

	bool InPlayerZone();
};

