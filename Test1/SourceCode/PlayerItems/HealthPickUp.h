#pragma once

#include "PickUp.h"
#include "../Constraints.h"
#include "../Player/PlayerHealth.h"

class CHealthPickUp : public CPickUp
{
public:
	CHealthPickUp();

protected:
	void InContactWithPlayer();
};

