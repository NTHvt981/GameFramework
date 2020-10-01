#include "Entity.h"

CEntity::CEntity(LPCWSTR texturePath)
{
	this->texture = CGraphic::Instance->LoadTexture(texturePath);
}

void CEntity::SetPosition(float _x, float _y)
{
	position.x = _x;
	position.y = _y;
}

Vector CEntity::GetPosition()
{
	return position;
}


void CEntity::move(DWORD dt)
{
	list<LPEntity> objectsCollide;
	collisionBox->CalculateCollision(velocity, objectsCollide);
	position = position + velocity;
}

void CEntity::SetCollisionBox(LPCollisionBox _collisionBox)
{
	this->collisionBox = _collisionBox;
}

LPCollisionBox CEntity::GetCollisionBox()
{
	return collisionBox;
}

void CEntity::Update(DWORD dt)
{
}

void CEntity::Render()
{
	CGraphic::Instance->Draw(
		position,
		origin,
		texture
	);
}

CEntity::~CEntity()
{
	//Free memory
	if (texture != NULL) texture->Release();
}
