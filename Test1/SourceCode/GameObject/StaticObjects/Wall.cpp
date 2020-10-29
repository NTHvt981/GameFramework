#include "Wall.h"

CWall::CWall(float l, float t, float r, float b): CEntity()
{
	collisionBox = new CDynamicBox(this);
	collisionBox->SetLTRB(l, t, r, b);
	collisionBox->SetSolid(true);

	SetType(GOTYPES::Wall);
}

void CWall::Render()
{
	collisionBox->Render();
}
