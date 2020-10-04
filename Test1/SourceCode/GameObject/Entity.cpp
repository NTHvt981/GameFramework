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
		collisionBox->CalculateCollision(velocity, collideEvents);
	position = position + velocity;
	collisionBox->Update();
}

LPDynamicBox CEntity::GetCollisionBox()
{
	return collisionBox;
}

bool CEntity::IsCollidedWith(GOTYPES type)
{
	for each (CollisionEvent e in collideEvents)
	{
		if (e.object->GetType() == type)
			return true;
	}
	return false;
}

bool CEntity::GetCollidedWith(GOTYPES type, list<LPGameObject>& collidedObjs)
{
	bool result = false;
	collidedObjs.clear();
	for each (CollisionEvent e in collideEvents)
	{
		if (e.object->GetType() == type)
		{
			result = true;
		
			collidedObjs.push_back(e.object);
		}
	}

	return result;
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
