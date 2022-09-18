#include "Entity.h"

CEntity::CEntity() : CGameObject()
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

void CEntity::SetId(int64_t _id)
{
	id = _id;
}

Vector CEntity::GetPosition()
{
	return position;
}

void CEntity::SetCenter(float _x, float _y)
{
	Vector size = collisionBox->GetSize();
	Vector col_local_pos = collisionBox->GetLocalPosition();
	float pos_x = _x - size.x / 2 - col_local_pos.x;
	float pos_y = _y - size.y / 2 - col_local_pos.y;

	SetPosition(pos_x, pos_y);
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

int64_t CEntity::GetId() const
{
	return id;
}

void CEntity::Move(DWORD dt)
{
	velocity.y += gravity;
	MoveWithoutGravity(dt);
}

void CEntity::MoveWithoutGravity(DWORD dt)
{
	Vector vel_x(velocity.x, 0);
	Vector vel_y(0, velocity.y);

	collideEvents.clear();

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
	}
}

bool CEntity::IsColliding(LPEntity entity)
{
	return collisionBox->IsColliding(entity->GetCollisionBox());
}

//void CEntity::SetMaxHealth(int64_t mh)
//{
//	maxHealth = mh;
//	health = mh;
//}
//
//int64_t CEntity::GetHealth()
//{
//	return health;
//}
//
//void CEntity::InflictDamage(int64_t dam)
//{
//	health = max(0, health - dam);
//}

LPDynamicBox CEntity::GetCollisionBox()
{
	return collisionBox;
}

bool CEntity::IsCollidedWith(GOTYPES Type)
{
	for (const CollisionEvent& e: collideEvents)
	{
		if (e.object->GetType() == Type)
		{
			return true;
		}
	}
	return false;
}

bool CEntity::GetCollidedWith(GOTYPES Type, std::list<LPGameObject>& collidedObjs)
{
	bool result = false;
	collidedObjs.clear();
	for (const CollisionEvent& e: collideEvents)
	{
		if (e.object->GetType() == Type)
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

void CEntity::GetGridPosition(int64_t& x, int64_t& y)
{
	x = gridX;
	y = gridY;
}

void CEntity::SetGridPosition(int64_t x, int64_t y)
{
	gridX = x;
	gridY = y;
}

bool CheckCollision(LPEntity a, LPEntity b)
{
	return CheckCollision(a->GetCollisionBox(), b->GetCollisionBox());
}
