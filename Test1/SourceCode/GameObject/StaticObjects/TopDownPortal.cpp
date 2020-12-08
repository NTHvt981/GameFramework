#include "TopDownPortal.h"

CTopDownPortal::CTopDownPortal(float l, float t, float r, float b) : CEntity()
{
	collisionBox = new CDynamicBox(this);
	collisionBox->SetLTRB(l, t, r, b);
	collisionBox->SetSolid(false);

	velocity = Vector(0, 0);
	position = Vector((r + l) / 2, (t + b) / 2);

	SetType(GOTYPES::AreaPortal);
}

void CTopDownPortal::Update(DWORD dt)
{
	collisionBox->GetCollision(
		collideEvents
	);
}

void CTopDownPortal::Render()
{
	collisionBox->Render();
}

bool CTopDownPortal::IsCollideWithPlayer()
{
	bool collidePlayer = IsColliding(CPlayer::GetCurrentPlayer());

	if (!alreadyCollideWithPlayer && collidePlayer)
	{
		alreadyCollideWithPlayer = true;
		return true;
	}

	if (alreadyCollideWithPlayer && (!collidePlayer))
		alreadyCollideWithPlayer = false;

	return false;
}

void CTopDownPortal::SetIsCollideWithPlayer(bool b)
{
	alreadyCollideWithPlayer = b;
}

void CTopDownPortal::GetLTRB(float& l, float& t, float& r, float& b)
{
	collisionBox->GetLTRB(l, t, r, b);
}

void CTopDownPortal::SetLTRB(float l, float t, float r, float b)
{
	collisionBox->SetLTRB(l, t, r, b);
}