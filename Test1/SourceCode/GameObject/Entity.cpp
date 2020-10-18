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
	Vector vel_x(velocity.x, 0);
	Vector vel_y(0, velocity.y);

	if (collisionBox != NULL)
	{
		collisionBox->CalculateCollision(vel_x, collideEvents);
		position.x = position.x + vel_x.x;
		velocity.x = vel_x.x;
		collisionBox->Update();

		collisionBox->CalculateCollision(vel_y, collideEvents);
		position.y = position.y + vel_y.y;
		velocity.y = vel_y.y;
		collisionBox->Update();
	}
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
