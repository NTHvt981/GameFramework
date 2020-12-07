#include "Portal.h"

CAreaPortal::CAreaPortal(float l, float t, float r, float b, int p, int a) : CEntity()
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

void CAreaPortal::SetTargetId(int t)
{
	targetId = t;
}

int CAreaPortal::GetTargetId()
{
	return targetId;
}

void CAreaPortal::SetArea(CArea* a)
{
	this->area = a;
}

CArea* CAreaPortal::GetArea()
{
	return this->area;
}

void CAreaPortal::SetAreaId(int area)
{
	areaId = area;
}

int CAreaPortal::GetAreaId()
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
	bool collidePlayer;
	IsColliding(CPlayer::GetCurrentPlayer(), collidePlayer);

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
