#include "GameObject.h"

void CGameObject::move(DWORD dt)
{
	list<LPGameObject> objectsCollide;
	collisionBox->CalculateCollision(velocity, objectsCollide);
	if (objectsCollide.size() > 0)
		DebugOut(L"COLLIDE\n");
	position = position + velocity;
}

CGameObject::CGameObject(LPCWSTR texturePath)
{
	this->texture = CGraphic::Instance->LoadTexture(texturePath);
}

void CGameObject::SetPosition(float _x, float _y)
{
	position.x = _x;
	position.y = _y;
}

Vector CGameObject::GetPosition()
{
	return position;
}

void CGameObject::SetCollisionBox(LPCollisionBox _collisionBox)
{
	this->collisionBox = _collisionBox;
}

LPCollisionBox CGameObject::GetCollisionBox()
{
	return collisionBox;
}

void CGameObject::Update(DWORD dt)
{
}

void CGameObject::Render()
{
	CGraphic::Instance->Draw(position, texture);
}

CGameObject::~CGameObject()
{
	//Free memory
	if (texture != NULL) texture->Release();
}
