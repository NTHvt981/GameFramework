#include "Portal.h"

CPortal::CPortal(float l, float t, float r, float b, int p) : CEntity()
{
	collisionBox = new CDynamicBox(this);
	collisionBox->SetLTRB(l, t, r, b);
	collisionBox->SetSolid(false);

	velocity = Vector(0, 0);
	position = Vector((r + l) / 2, (t + b) / 2);

	this->targetId = p;

	SetType(GOTYPES::Porter);
}

void CPortal::SetTargetId(int t)
{
	targetId = t;
}

int CPortal::GetTargetId()
{
	return targetId;
}

void CPortal::SetArea(CArea* a)
{
	this->area = a;
}

CArea* CPortal::GetArea()
{
	return this->area;
}

void CPortal::SetAreaId(int area)
{
	areaId = area;
}

int CPortal::GetAreaId()
{
	return areaId;
}

void CPortal::Update(DWORD dt)
{
	collisionBox->GetCollision(
		collideEvents
	);
}

void CPortal::Render()
{
	collisionBox->Render();
}

bool CPortal::IsCollideWithPlayer()
{
	if (!alreadyCollideWithPlayer && IsCollidedWith(GOTYPES::Player))
	{
		alreadyCollideWithPlayer = true;
		return true;
	}

	if (alreadyCollideWithPlayer && (!IsCollidedWith(GOTYPES::Player)))
		alreadyCollideWithPlayer = false;

	return false;
}

void CPortal::SetIsCollideWithPlayer(bool b)
{
	alreadyCollideWithPlayer = b;
}

void CPortal::SetDeploySide(int s)
{
	if (s == 1)
		localDeployPosition.x = 16;
	else
		localDeployPosition.x = -16;
	localDeployPosition.y = 8;
}

void CPortal::GetDeployPosition(float& x, float& y)
{
	x = GetCenter().x + localDeployPosition.x;
	y = GetCenter().y + localDeployPosition.y;
}
