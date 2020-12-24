#include "Jumper.h"

void CJumper::NormalState(DWORD dt)
{
	bool onEdgeCon = collisionBox->IsHypothesizedColliding(
		position.x,
		position.y + 1
	) && (! collisionBox->IsHypothesizedColliding(
			position.x + width * facing,
			position.y + 1
		));

	bool hitWallCon = collisionBox->IsHypothesizedColliding(
		position.x + facing,
		position.y
	);

	if (onEdgeCon || hitWallCon)
		facing = -facing;

	velocity.x = facing * normalSpeed;

	old_velocity.Set(velocity.x, velocity.y);
	Move(dt);

	if (DistanceToPlayer() < innerRadius)
		state = JUMPER_CHASE_PLAYER;
}

void CJumper::ChasePlayerState(DWORD dt)
{
	Vector playerPos = CPlayer::GetCurrentPlayer()->GetCenter();
	Vector selfPos = GetCenter();

	if ((playerPos.x - selfPos.x > 25) && (facing == -1))
		facing = 1;
	else if ((selfPos.x - playerPos.x > 25) && (facing == 1))
		facing = -1;

	velocity.x = facing * chaseSpeed;

	if (collisionBox->IsHypothesizedColliding(position.x, position.y + 1))
		velocity.y -= jumpSpeed;

	old_velocity.Set(velocity.x, velocity.y);
	Move(dt);

	if (DistanceToPlayer() > outerRadius)
		state = JUMPER_NORMAL;
}

CJumper::CJumper() : CEnemy()
{
	SetType(GOTYPES::Enemy);
	gravity = 0.2;
	jumpSpeed = 6;

	this->collisionBox = new CDynamicBox(
		this,
		0, 0,
		17, 26
	);
	collisionBox->SetSolid(false);

	moveLeftAni = new CAnimation(150);
	int idsL[] = {
		ID_JUMPER_MOVE_LEFT_1,
		ID_JUMPER_MOVE_LEFT_2,
		ID_JUMPER_MOVE_LEFT_3
	};

	moveLeftAni->Add(idsL, 3);

	moveRightAni = new CAnimation(150);
	int idsR[] = {
		ID_JUMPER_MOVE_RIGHT_1,
		ID_JUMPER_MOVE_RIGHT_2,
		ID_JUMPER_MOVE_RIGHT_3
	};

	moveRightAni->Add(idsR, 3);
	animation = moveLeftAni;

	moveLeftAni->GetSize(width, height);
}

void CJumper::Update(DWORD dt)
{
	if (state == JUMPER_NORMAL)
		NormalState(dt);
	else
		ChasePlayerState(dt);

	if (facing == JUMPER_LEFT)
		animation = moveLeftAni;
	else
		animation = moveRightAni;
}

void CJumper::Render()
{
	animation->Render(position.x, position.y);
	collisionBox->Render();
}