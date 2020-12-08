#pragma once

#include "../Entity.h"
#include "../../Constraints.h"
#include "../../SceneSystem/SceneRequest.h"

#include "../../Player/Player.h"

class CEnemy : public CEntity
{
protected:
	int maxHealth;
	int health;
	Vector old_velocity;
	void SetMaxHealth(int mh);

	int width;
	int height;

public:
	CEnemy();

	virtual void Update(DWORD dt);

	virtual void InflictDamage(int dam);

	float DistanceToPlayer();
	float HorizontalDistanceToPlayer();
	float VerticalDistanceToPlayer();
};

