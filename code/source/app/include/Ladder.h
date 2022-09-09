#pragma once

#include "Entity.h"
#include "CollisionBox.h"

class CLadder : public CEntity
{
protected:
	void Move(DWORD dt);
public:
	void SetPosition(float _x, float _y);
	CLadder(float l, float t, float r, float b);
	void Render();
};

