#include "Wall.h"

void CWall::move(DWORD dt)
{
	// TODO: do nothing, wall is not meant to move
}

CWall::CWall(float l, float t, float r, float b): CEntity(NULL)
{
	collisionBox = new CCollisionBox(this, 0, 0, 0, 0);
	collisionBox->SetSolid(true);
	collisionBox->SetLTRB(l, t, r, b);
}

void CWall::Render()
{
	collisionBox->Render();
}
