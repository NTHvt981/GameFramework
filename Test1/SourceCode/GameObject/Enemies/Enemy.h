#pragma once

#include "../Entity.h"
#include "../../Constraints.h"
#include "../../Game/GameRequest.h"

class CEnemy : public CEntity
{
protected:
	int maxHealth;
	int health;
	void SetMaxHealth(int mh);

public:
	CEnemy();

	virtual void Update(DWORD dt);

	void InflictDamage(int dam);
};

