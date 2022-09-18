#pragma once

#include "Constraints.h"

class IPhysic
{
private:
	float gravity = 0.25;
protected:
	bool onGround = false;
	float jumpSpeed = 6.25;
	void ApplyPhysic(Vector &v);
};

