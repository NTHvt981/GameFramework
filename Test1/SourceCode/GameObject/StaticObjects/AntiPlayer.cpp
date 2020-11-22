#include "AntiPlayer.h"

void CAntiPlayer::move(DWORD dt)
{
}

void CAntiPlayer::SetPosition(float _x, float _y)
{

}

CAntiPlayer::CAntiPlayer(float l, float t, float r, float b) : CEntity()
{
	SetType(GOTYPES::Enemy);
	position = Vector(-1, -1);
	velocity = Vector(0, 0);

	collisionBox = new CDynamicBox(this);
	collisionBox->SetLTRB(l, t, r, b);
	collisionBox->SetSolid(false);
}

void CAntiPlayer::Render()
{
	collisionBox->Render();
}