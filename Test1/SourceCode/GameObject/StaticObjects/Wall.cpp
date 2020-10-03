#include "Wall.h"

void CWall::move(DWORD dt)
{
	// TODO: do nothing, wall is not meant to move
}

CWall::CWall(float l, float t, float r, float b): CGameObject()
{
	collisionBox = new CCollisionBox(this, 0, 0, 0, 0);
	collisionBox->SetSolid(true);
	collisionBox->SetLTRB(l, t, r, b);

	SetType(GOTYPES::Wall);
}

void CWall::Render()
{
	collisionBox->Render();
}
