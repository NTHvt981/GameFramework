#pragma once

#include "Entity.h"
#include "CollisionBox.h"

class CAntiPlayer: public CEntity
{
protected:
	void Move(DWORD dt);
public:
	CAntiPlayer(float l, float t, float r, float b);

	void SetPosition(float _x, float _y);
	void Render();
};

