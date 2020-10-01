#pragma once

#include "../Entity.h"
#include "../../Constraints.h"
#include "../../Camera/Camera.h"
#include "../../Input/Input.h"

class CPlayer: public CEntity
{
private:
	float speed = 2;
	CCamera* camera;
public:
	CPlayer(LPCWSTR texturePath);
	void Update(DWORD dt);
	void Render();
};

