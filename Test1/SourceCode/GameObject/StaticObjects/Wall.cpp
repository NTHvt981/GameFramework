#include "Wall.h"

CWall::CWall(float l, float t, float r, float b): CGameObject()
{
	collisionBox = new CCollisionBox(this, l, t, r, b);
	collisionBox->SetSolid(true);

	SetType(GOTYPES::Wall);
}

void CWall::Render()
{
	collisionBox->Render();
}
