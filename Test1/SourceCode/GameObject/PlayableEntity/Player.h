#pragma once

#include "../Entity.h"
#include "../../Constraints.h"
#include "../../Camera/Camera.h"
#include "../../Input/Input.h"
#include "../../Unit/Animation.h"

class CPlayer: public CEntity
{
private:
	float speed = 2;
	CCamera* camera;

	Vector left_wheel_pivot = Vector(-6, -4);
	Vector right_wheel_pivot = Vector(6, -4);

	LPAnimation left_wheel_ani;
	LPAnimation right_wheel_ani;
public:
	CPlayer(LPCWSTR texturePath);
	void Update(DWORD dt);
	void Render();
};

