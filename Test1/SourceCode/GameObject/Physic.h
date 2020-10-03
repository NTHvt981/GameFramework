#pragma once

#include "..\Constraints.h"

class IPhysic
{
private:
	float gravity = 0.5;
protected:
	bool onGround = false;
	float jumpSpeed = 10;
	void ApplyPhysic(Vector &v);
};

