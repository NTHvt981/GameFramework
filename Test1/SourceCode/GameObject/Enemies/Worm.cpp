#include "Worm.h"

void CWorm::NormalState(DWORD dt)
{
	animation->SetSpeed(1);

	velocity.x = facing * normalSpeed;

	old_velocity.Set(velocity.x, velocity.y);
	Move(dt);

	bool onEdgeCon = collisionBox->IsHypothesizedColliding(
		position.x,
		position.y + 1
	) && (!collisionBox->IsHypothesizedColliding(
		position.x + width * facing,
		position.y + 1
	));

	bool hitWallCon = collisionBox->IsHypothesizedColliding(
		position.x + facing,
		position.y
	);

	if (onEdgeCon || hitWallCon)
		facing = -facing;

	if (DistanceToPlayer() < innerRadius)
		state = WORM_CHASE_PLAYER;
}

void CWorm::ChasePlayerState(DWORD dt)
{
	animation->SetSpeed(2);

	bool hitWallCon = collisionBox->IsHypothesizedColliding(
		position.x + facing,
		position.y
	);
	bool onGroundCon = collisionBox->IsHypothesizedColliding(position.x, position.y + 1);

	Vector playerPos = CPlayer::GetCurrentPlayer()->GetCenter();
	Vector selfPos = GetCenter();

	if ((playerPos.x - selfPos.x > chaseLimit) && (facing == -1))
		facing = 1;
	else if ((selfPos.x - playerPos.x > chaseLimit) && (facing == 1))
		facing = -1;

	velocity.x = facing * chaseSpeed;

	if (hitWallCon && onGroundCon)
		velocity.y -= jumpSpeed;

	old_velocity.Set(velocity.x, velocity.y);
	Move(dt);

	if (DistanceToPlayer() > outerRadius)
		state = WORM_NORMAL;
}

CWorm::CWorm() : CEnemy()
{
	SetMaxHealth(4);
	CEntity::gravity = gravity;
	CEntity::jumpSpeed = jumpSpeed;

	moveLeftAni = new CAnimation(1, 200);
	int idsL[] = {
		ID_WORM_MOVE_LEFT_1,
		ID_WORM_MOVE_LEFT_2
	};

	moveLeftAni->Add(idsL, 2);

	moveRightAni = new CAnimation(1, 200);
	int idsR[] = {
		ID_WORM_MOVE_RIGHT_1,
		ID_WORM_MOVE_RIGHT_2
	};

	moveRightAni->Add(idsR, 2);
	animation = moveRightAni;

	animation->GetSize(width, height);
	this->collisionBox = new CDynamicBox(
		this,
		0, 0,
		width, height
	);
	collisionBox->SetSolid(false);
}

void CWorm::Update(DWORD dt)
{
	switch (state)
	{
	case WORM_NORMAL:
		NormalState(dt);
		break;
	case WORM_CHASE_PLAYER:
		ChasePlayerState(dt);
		break;
	}

	if (facing == WORM_LEFT)
		animation = moveLeftAni;
	else
		animation = moveRightAni;
}

void CWorm::Render()
{
	animation->Render(position);
	collisionBox->Render();
}

