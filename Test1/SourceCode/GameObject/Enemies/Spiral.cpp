#include "Spiral.h"

CSpiral::CSpiral()
{
	animation = new CAnimation(500);

	animation->Add(ID_SPIRAL_LEFT_1);
	animation->Add(ID_SPIRAL_LEFT_2);
	animation->Add(ID_SPIRAL_RIGHT_1);
	animation->Add(ID_SPIRAL_RIGHT_2);

	animation->GetSize(width, height);

	collisionBox = new CDynamicBox(
		this, 0, 0,
		width, height
	);
	collisionBox->SetSolid(false);

	SetMaxHealth(SPIRAL_HEALTH);
}

void CSpiral::Shoot()
{
	Vector center = GetCenter();

	CSpiralBullet::Create(
		center.x + 20, center.y,
		center, ID_ENEMY_TOPDOWN_BULLET_1, 3000);
	CSpiralBullet::Create(
		center.x - 20, center.y,
		center, ID_ENEMY_TOPDOWN_BULLET_1, 3000);
	CSpiralBullet::Create(
		center.x, center.y + 20,
		center, ID_ENEMY_TOPDOWN_BULLET_1, 3000);
	CSpiralBullet::Create(
		center.x, center.y - 20,
		center, ID_ENEMY_TOPDOWN_BULLET_1, 3000);

	CSoundLibrary::GetInstance()->PlayEnemyShootSound();
}

void CSpiral::Update(DWORD dt)
{
	if (isHurt)
	{
		shootCountUp += dt;
		if (shootCountUp >= shootWaitTime)
		{
			shootCountUp = 0;
			Shoot();
		}
	}
}

void CSpiral::Render()
{
	animation->Render(position);
	collisionBox->Render();
}

void CSpiral::InflictDamage(int dam)
{
	CEnemy::InflictDamage(dam);
	isHurt = true;
}
