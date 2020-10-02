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
	if (collisionBox != NULL)
		collisionBox->CalculateCollision(velocity, objectsCollide);
	position = position + velocity;
	collisionBox->Update();
}

void CEntity::SetCollisionBox(LPCollisionBox _collisionBox)
{
	this->collisionBox = _collisionBox;
}

LPCollisionBox CEntity::GetCollisionBox()
{
	return collisionBox;
}

void CEntity::RenderBoundingBox()
{
	// TODO: Don't render collision box here
}

void CEntity::Update(DWORD dt)
{
}

void CEntity::Render()
{
	CGraphic::Instance->Draw(
		texture,
		position,
		origin
	);
}

CEntity::~CEntity()
{
	//Free memory
	if (texture != NULL) texture->Release();
}
