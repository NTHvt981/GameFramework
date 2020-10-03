#include "Entity.h"

CEntity::CEntity(LPCWSTR texturePath)
{
	this->texture = CGraphic::Instance->LoadTexture(texturePath);
	SetType(GOTYPES::Entity);
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

//void CEntity::SetCollisionBox(LPCollisionBox _collisionBox)
//{
//	this->collisionBox = _collisionBox;
//}

LPDynamicBox CEntity::GetCollisionBox()
{
	return collisionBox;
}

bool CEntity::IsCollidedWith(GOTYPES type)
{
	for (const LPGameObject& e : collidedEntities)
	{
		if (e ->GetType() == type)
			return true;
	}
	return false;
}

void CEntity::GetCollidedWith(GOTYPES type, list<LPGameObject>& collidedObjs)
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
