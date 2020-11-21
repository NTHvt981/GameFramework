#include "Wall.h"

void CWall::move(DWORD dt)
{
}

void CWall::SetPosition(float _x, float _y)
{

}

CWall::CWall(float l, float t, float r, float b): CEntity()
{
	position = Vector(-1, -1);
	velocity = Vector(0, 0);

	collisionBox = new CDynamicBox(this);
	collisionBox->SetLTRB(l, t, r, b);
	collisionBox->SetSolid(true);

	SetType(GOTYPES::Wall);
}

void CWall::Render()
{
	collisionBox->Render();
}
