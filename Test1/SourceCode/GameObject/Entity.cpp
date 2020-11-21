#include "Entity.h"

CEntity::CEntity()
{
	SetType(GOTYPES::Entity);
}

void CEntity::SetPosition(float _x, float _y)
{
	position.x = _x;
	position.y = _y;

	//when we change position of entity, 
	//we should update the collision box
	collisionBox->Update();
}

void CEntity::SetId(int _id)
{
	id = _id;
}

Vector CEntity::GetPosition()
{
	return position;
}

Vector CEntity::GetCenter()
{
	float l, t, r, b;
	collisionBox->GetLTRB(l, t, r, b);

	return Vector(
		(r + l) / 2,
		(b + t) / 2
	);
}

int CEntity::GetId()
{
	return id;
}


void CEntity::move(DWORD dt)
{
	velocity.y += gravity;

	Vector vel_x(velocity.x, 0);
	Vector vel_y(0, velocity.y);

	//collisionBox->ResetCoCollisionBoxes();
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

		//collisionBox->CalculateCollision(velocity, collideEvents);
		//position = position + velocity;
		//collisionBox->Update();
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
}

CEntity::~CEntity()
{
	//Free memory here
}
