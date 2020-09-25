#pragma once

#include "../GameObject.h"
#include "../../Constraints.h"
#include "../../Camera/Camera.h"

class CPlayer: public CGameObject
{
private:
	float speed = 0.5;
	CCamera* camera;
public:
	CPlayer(LPCWSTR texturePath);
	void Update(DWORD dt);
};

