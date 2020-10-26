#pragma once

#include "..\Entity.h"
#include "..\..\Collision\CollisionBox.h"

class CWall: public CEntity
{
protected:
	LPCollisionBox collisionBox = NULL;
public:
	CWall(float l, float t, float r, float b);
	void Render();
};

