#pragma once

#include "..\Constraints.h"

class IPhysic
{
private:
	float gravity = 0.5;
protected:
	bool onGround = false;
	float jumpSpeed = 8;
	void ApplyPhysic(Vector &v);
};

