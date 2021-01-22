#include "EyeBall.h"

void CEyeBall::MoveRandom(DWORD dt)
{
	moveCountUp += dt;
	if (moveCountUp >= moveWaitTime)
	{
		moveCountUp = 0;

		moveDir.x = CUtils::randFloatRange(-1, 1);
		moveDir.y = CUtils::randFloatRange(-1, 1);
	}

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
}

void CEyeBall::Shoot(DWORD dt)
{
	shootCountUp += dt;

	bool con_1 = shootCountUp >= shootWaitTime;
	bool con_2 = InPlayerZone();
	bool con_3 = animation->GetCurrentFrame() != 3;

	if (con_1 &&  con_2 && con_3)
	{
		shootCountUp = 0;
		shootWaitTime = CUtils::randRange(100, 200);

		Vector center = GetCenter();
		Vector pCenter = CPlayer::GetCurrentPlayer()->GetCenter();
		Vector dir = Vector(pCenter.x - center.x, pCenter.y - center.y);
		CEnemyBullet::Create(
			center.x, center.y, dir, EYEBALL_BULLET_SPEED, 0, ID_ENEMY_TOPDOWN_BULLET_1, 300, true
		);

		CSoundLibrary::GetInstance()->PlayEnemyShootSound();
	}
}

CEyeBall::CEyeBall(int _type): CEnemy()
{
	animation = new CAnimation(400);
	animation->Add(ID_EYEBALL_1);
	animation->Add(ID_EYEBALL_3);
	animation->Add(ID_EYEBALL_1);
	animation->Add(ID_EYEBALL_2, 700);
	animation->Add(ID_EYEBALL_3);
	animation->Add(ID_EYEBALL_1);
	animation->Add(ID_EYEBALL_3);

	animation->GetSize(width, height);
	collisionBox = new CDynamicBox(
		this, 0, 0,
		width, height
	);
	collisionBox->SetSolid(false);

	type = _type;
}

void CEyeBall::Update(DWORD dt)
{
	Shoot(dt);

	if (type != EYEBALL_TYPE_IDLE)
		MoveRandom(dt);
}

void CEyeBall::Render()
{
	animation->Render(position);
	collisionBox->Render();
}
