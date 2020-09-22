#include "HorizontalEntity.h"

CHorizontalEntity::CHorizontalEntity(LPCWSTR texturePath):CGameObject(texturePath)
{
	vx = 0.2;
}

void CHorizontalEntity::Update(DWORD dt)
{
	if (x <= 0)
		vx = 0.2;
	else if (x >= WINDOW_WIDTH)
		vx = -0.2;

	move(dt);
}
