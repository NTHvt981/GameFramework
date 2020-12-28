#pragma once

#include "PickUp.h"
#include "../Constraints.h"
#include "../Player/PlayerHealth.h"

#define HEALTH_INCREASE 3

class CHealthPickUp : public CPickUp
{
public:
	CHealthPickUp();

protected:
	void InContactWithPlayer();
};

