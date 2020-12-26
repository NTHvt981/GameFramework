#include "Walker.h"

void CWalker::MoveState(DWORD dt)
{
	velocity.x = moveDir.x * speed;
	velocity.y = moveDir.y * speed;

	Move(dt);

	if (collisionBox->IsHypothesizedColliding(
		position.x + moveDir.x, position.y
	))
		moveDir.x *= -1;

	if (collisionBox->IsHypothesizedColliding(
		position.x, position.y + moveDir.y
	))
		moveDir.y *= -1;


	countUp += dt;
	if (countUp >= moveWaitTime)
	{
		countUp = 0;
		state = WALKER_IDLE;
	}
}

void CWalker::IdleState(DWORD dt)
{
	if (!stopShoot && InPlayerZone())
	{
		stopShoot = true;

		Vector center = GetCenter();
		Vector pCenter = CPlayer::GetCurrentPlayer()->GetCenter();
		Vector dir = Vector(pCenter.x - center.x, pCenter.y - center.y);
		CEnemyBullet::Create(
			center.x, center.y, dir, WALKER_BULLET_SPEED, 0, ID_ENEMY_TOPDOWN_BULLET_1, 300, true
		);
	}

	countUp += dt;
	if (countUp >= stopWaitTime)
	{
		countUp = 0;
		state = WALKER_MOVE;

		stopShoot = false;
	}

	velocity.Set(0, 0);
}

void CWalker::GetSetAnimation(DWORD dt)
{
	if (velocity.y > 0 || velocity.x > 0)
	{
		currentAni->SetMode(ANIMATION_NORMAL);
		currentAni = moveDownAni;
	}
	else if (velocity.y < 0 || velocity.x < 0)
	{
		currentAni->SetMode(ANIMATION_NORMAL);
		currentAni = moveUpAni;
	}
	else
		currentAni->SetMode(ANIMATION_PAUSE);
}

CWalker::CWalker() : CEnemy()
{
	SetType(GOTYPES::Enemy);
	speed = WALKER_MOVE_SPEED;

	this->collisionBox = new CDynamicBox(
		this,
		0, 0,
		18, 17
	);
	collisionBox->SetSolid(false);

	moveDownAni = new CAnimation(200);
	moveUpAni = new CAnimation(200);

	moveDownAni->Add(ID_WALKER_1);
	moveDownAni->Add(ID_WALKER_2);
	moveDownAni->Add(ID_WALKER_4);
	moveDownAni->Add(ID_WALKER_3);

	moveUpAni->Add(ID_WALKER_3);
	moveUpAni->Add(ID_WALKER_4);
	moveUpAni->Add(ID_WALKER_2);
	moveUpAni->Add(ID_WALKER_1);

	currentAni = moveDownAni;
	currentAni->SetMode(ANIMATION_PAUSE);
}

void CWalker::Update(DWORD dt)
{
	switch (state)
	{
	case WALKER_MOVE:
		MoveState(dt);
		break;
	case WALKER_IDLE:
		IdleState(dt);
		break;
	default:
		break;
	}

	if (InPlayerZone())
		MoveTowardPlayer(dt);
	else
		MoveRandom(dt);

	GetSetAnimation(dt);
}


void CWalker::MoveRandom(DWORD dt)
{
	velocityCountUp += dt;
	if (velocityCountUp >= velocityWaitTime)
	{
		velocityCountUp = 0;

		moveDir.x = CUtils::randRange(-1, 1);
		moveDir.y = CUtils::randRange(-1, 1);
	}
}

void CWalker::MoveTowardPlayer(DWORD dt)
{
	Vector center = GetCenter();
	Vector playerCenter = CPlayer::GetCurrentPlayer()->GetCenter();
	float distance = DistanceToPlayer();

	moveDir.x = (playerCenter.x - center.x) / distance;
	moveDir.y = (playerCenter.y - center.y) / distance;
}

void CWalker::Render()
{
	currentAni->Render(position);
	collisionBox->Render();
}
