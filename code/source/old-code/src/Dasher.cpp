#include "Dasher.h"

CDasher::CDasher(int64_t _type): CEnemy()
{
	type = _type;

	idleAni = new CAnimation(400);
	idleAni->Add(ID_DASHER_IDLE_1);
	idleAni->Add(ID_DASHER_IDLE_2);
	idleAni->Add(ID_DASHER_IDLE_3);
	idleAni->Add(ID_DASHER_IDLE_4);

	moveAni = new CAnimation(200);
	moveAni->Add(ID_DASHER_MOVE_1);
	moveAni->Add(ID_DASHER_MOVE_2);
	moveAni->Add(ID_DASHER_MOVE_3);
	moveAni->Add(ID_DASHER_MOVE_4);

	animation = idleAni;

	animation->GetSize(width, height);
	collisionBox = new CDynamicBox(
		this, -width / 2, -height / 2,
		width, height
	);
	collisionBox->SetSolid(false);
}

void CDasher::Update(DWORD dt)
{
	switch (state)
	{
	case DASHER_IDLE:
		IdleState(dt);
		break;
	case DASHER_MOVE:
		MoveState(dt);
		break;
	default:
		break;
	}
}

void CDasher::IdleState(DWORD dt)
{
	animation = idleAni;

	float range;
	int64_t side;
	if (type == DASHER_HORIZONTAL)
	{
		range = VerticalDistanceToPlayer();
		int64_t side = CPlayer::GetCurrentPlayer()->GetCenter().x - position.x > 0 ? 1 : -1;
		velocity.x = side * speed;
	}
	else
	{
		range = HorizontalDistanceToPlayer();
		int64_t side = CPlayer::GetCurrentPlayer()->GetCenter().y - position.y > 0 ? 1 : -1;
		velocity.y = side * speed;
	}

	if (range <= maxRange)
	{
		state = DASHER_MOVE;
	}
}

void CDasher::MoveState(DWORD dt)
{
	animation = moveAni;

	Move(dt);
	if (velocity.y == 0 && velocity.x == 0)
		state = DASHER_IDLE;

}

void CDasher::Render()
{
	animation->Render(position.x - width / 2, position.y - height / 2);
	collisionBox->Render();
}
