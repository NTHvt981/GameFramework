#include "Skull.h"

void CSkull::NormalState(DWORD dt)
{
	bool hitWallCon = collisionBox->IsHypothesizedColliding(
		position.x + facing,
		position.y
	);

	if (hitWallCon)
		facing = -facing;

	velocity.x = facing * horizontalSpeed;
	velocity.y = 0;
	distanceTravel = 0;

	old_velocity.Set(velocity.x, velocity.y);
	Move(dt);

	if (HorizontalDistanceToPlayer() < horizontalRadius && 
		VerticalDistanceToPlayer() < verticalRadius)
		state = SKULL_FLY_ABOVE;
}

void CSkull::FlyAboveState(DWORD dt)
{
	velocity.x = 0;
	velocity.y = -verticalSpeed;

	old_velocity.Set(velocity.x, velocity.y);
	Move(dt);
	distanceTravel -= velocity.y;

	bool hitWallCon = collisionBox->IsHypothesizedColliding(
		position.x,
		position.y - 1
	);

	bool hitMaxDistance = distanceTravel > maxDistanceTravel;

	if (hitWallCon || hitMaxDistance) state = SKULL_DROP_BOMB;
}

void CSkull::DropBombState(DWORD dt)
{
	Vector playerPos = CPlayer::GetCurrentPlayer()->GetCenter();
	Vector selfPos = GetCenter();

	if (playerPos.x > selfPos.x)
		facing = 1;
	else if (selfPos.x > playerPos.x)
		facing = -1;

	state = SKULL_FLY_BELOW;

	LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::CreateEntity);
	request->entity = new CEnemyBullet(
		Vector(facing, 0),
		1,
		0.4,
		ID_SKULL_BULLET,
		350,
		false
	);
	request->x = position.x + width/2;
	request->y = position.y + height/2;

	CSceneRequest::AddRequest(request);

	CSoundLibrary::GetInstance()->PlayEnemyShootSound();
}

void CSkull::FlyBelowState(DWORD dt)
{
	velocity.x = 0;
	velocity.y = verticalSpeed;

	old_velocity.Set(velocity.x, velocity.y);
	Move(dt);
	distanceTravel -= velocity.y;

	bool hitWallCon = collisionBox->IsHypothesizedColliding(
		position.x,
		position.y + 1
	);

	bool hitMaxDistance = distanceTravel < 0;

	if (hitWallCon || hitMaxDistance) state = SKULL_NORMAL;
}

CSkull::CSkull()
{
	SetType(GOTYPES::Enemy);

	this->collisionBox = new CDynamicBox(
		this,
		0, 0,
		18, 18
	);
	collisionBox->SetSolid(false);

	moveLeftAni = new CAnimation(750);
	int64_t idsL[] = {
		ID_SKULL_MOVE_LEFT_1,
		ID_SKULL_MOVE_LEFT_2
	};

	moveLeftAni->Add(idsL, 2);

	moveRightAni = new CAnimation(750);
	int64_t idsR[] = {
		ID_SKULL_MOVE_RIGHT_1,
		ID_SKULL_MOVE_RIGHT_2
	};

	moveRightAni->Add(idsR, 2);
	animation = moveLeftAni;

	moveLeftAni->GetSize(width, height);
}

void CSkull::Update(DWORD dt)
{
	switch (state)
	{
	case SKULL_NORMAL:
		NormalState(dt);
		break;
	case SKULL_FLY_ABOVE:
		FlyAboveState(dt);
		break;
	case SKULL_DROP_BOMB:
		DropBombState(dt);
		break;
	case SKULL_FLY_BELOW:
		FlyBelowState(dt);
		break;
	}

	if (facing == SKULL_LEFT)
		animation = moveLeftAni;
	else
		animation = moveRightAni;
}

void CSkull::Render()
{
	animation->Render(position.x, position.y);
	collisionBox->Render();
}
