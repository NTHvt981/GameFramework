#pragma once

#include "../GameObject.h"
#include "../../Constraints.h"
#include "../../Camera/Camera.h"
#include "../../Input/Input.h"

class CPlayer: public CGameObject
{
private:
	float speed = 2;
	CCamera* camera;
public:
	CPlayer(LPCWSTR texturePath);
	void Update(DWORD dt);
	void Render();
};

