#include "Ladder.h"

void CLadder::Move(DWORD dt)
{
}

void CLadder::SetPosition(float _x, float _y)
{

}

CLadder::CLadder(float l, float t, float r, float b) : CEntity()
{
	position = Vector(-1, -1);
	velocity = Vector(0, 0);

	collisionBox = new CDynamicBox(this);
	collisionBox->SetLTRB(l, t, r, b);
	collisionBox->SetSolid(true);

	SetType(GOTYPES::Ladder);
}

void CLadder::Render()
{
	collisionBox->Render();
}
