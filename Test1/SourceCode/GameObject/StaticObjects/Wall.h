#pragma once

#include "..\GameObject.h"
#include "..\..\Collision\CollisionBox.h"

class CWall: public CGameObject
{
protected:
	LPCollisionBox collisionBox = NULL;
public:
	CWall(float l, float t, float r, float b);
	void Render();
};

