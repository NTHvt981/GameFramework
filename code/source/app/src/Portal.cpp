#include "Portal.h"

CAreaPortal::CAreaPortal(float l, float t, float r, float b, int64_t p, int64_t a) : CEntity()
{
	collisionBox = new CDynamicBox(this);
	collisionBox->SetLTRB(l, t, r, b);
	collisionBox->SetSolid(false);

	velocity = Vector(0, 0);
	position = Vector((r + l) / 2, (t + b) / 2);

	this->targetId = p;
	this->areaId = a;

	SetType(GOTYPES::AreaPortal);
}

void CAreaPortal::SetTargetId(int64_t t)
{
	targetId = t;
}

int64_t CAreaPortal::GetTargetId()
{
	return targetId;
}

void CAreaPortal::SetArea(CArea* a)
{
	this->area = a;
}

CArea* CAreaPortal::GetArea() const
{
	return this->area;
}

void CAreaPortal::SetAreaId(int64_t area)
{
	areaId = area;
}

int64_t CAreaPortal::GetAreaId() const
{
	return areaId;
}

void CAreaPortal::Update(DWORD dt)
{
	collisionBox->GetCollision(
		collideEvents
	);
}

void CAreaPortal::Render()
{
	collisionBox->Render();
}

bool CAreaPortal::IsCollideWithPlayer()
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

void CAreaPortal::SetIsCollideWithPlayer(bool b)
{
	alreadyCollideWithPlayer = b;
}

void CAreaPortal::GetDeployPosition(float& x, float& y)
{
	x = GetCenter().x + (direction.x * distance);
	y = GetCenter().y + (direction.y * distance);
}

void CAreaPortal::GetLTRB(float& l, float& t, float& r, float& b)
{
	collisionBox->GetLTRB(l, t, r, b);
}

void CAreaPortal::SetLTRB(float l, float t, float r, float b)
{
	collisionBox->SetLTRB(l, t, r, b);
}

float CAreaPortal::GetDistance()
{
	return distance;
}

void CAreaPortal::SetDistance(float d)
{
	distance = d;
}

void CAreaPortal::SetDeployDirection(float x, float y)
{
	direction.x = x;
	direction.y = y;
}
