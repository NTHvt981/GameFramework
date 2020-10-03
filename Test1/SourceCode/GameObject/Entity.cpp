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
	if (collisionBox != NULL)
		collisionBox->CalculateCollision(velocity, collidedEntities);
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

bool CEntity::IsCollidedWith(GOTYPES type)
{
	for (const LPEntity& e : collidedEntities)
	{
		if (e ->GetType() == GOTYPES::Ground)
			return true;
	}
	//for (e = collidedEntities.begin(); e != collidedEntities.end(); e++)
	//{
	//	if (collidedEntities. e ->GetType() == GOTYPES::Ground)
	//		return true;
	//}
	return false;
}

void CEntity::GetCollidedWith(GOTYPES typee, list<LPEntity>& collidedObjs)
{
	collidedObjs.clear();
	for each (LPEntity e in collidedEntities)
	{
		if (e->GetType() == type)
			collidedObjs.push_back(e);
	}
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
