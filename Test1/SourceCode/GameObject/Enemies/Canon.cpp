#include "Canon.h"

CCanon::CCanon()
{
	animation = new CAnimation(500);
	animation->Add(ID_CANON_1);
	//2 -> shoot horizontal
	animation->Add(ID_CANON_2);
	animation->Add(ID_CANON_1);
	//2 -> shoot vertival
	animation->Add(ID_CANON_3);

	animation->GetSize(width, height);
	
	collisionBox = new CDynamicBox(
		this, -width / 2, -height / 2,
		width, height
	);
	collisionBox->SetSolid(false);
}

void CCanon::Update(DWORD dt)
{
	currFrame = animation->GetCurrentFrame();

	//Shoot horizontal
	if (currFrame == 1 && prevFrame == 0)
	{
		ShootHorizontal(dt);
	}

	if (currFrame == 3 && prevFrame == 2)
	{
		ShootVertical(dt);
	}

	prevFrame = currFrame;
}

void CCanon::ShootHorizontal(DWORD dt)
{
	CEnemyBullet::Create(
		position.x + span, 
		position.y, 
		Vector(1, 0), 
		CANON_BULLET_SPEED, 0, ID_ENEMY_TOPDOWN_BULLET_1, 300, true
	);

	CEnemyBullet::Create(
		position.x - span,
		position.y,
		Vector(-1, 0),
		CANON_BULLET_SPEED, 0, ID_ENEMY_TOPDOWN_BULLET_1, 300, true
	);
}

void CCanon::ShootVertical(DWORD dt)
{
	CEnemyBullet::Create(
		position.x,
		position.y + span,
		Vector(0, 1),
		CANON_BULLET_SPEED, 0, ID_ENEMY_TOPDOWN_BULLET_1, 300, true
	);

	CEnemyBullet::Create(
		position.x,
		position.y - span,
		Vector(0, -1),
		CANON_BULLET_SPEED, 0, ID_ENEMY_TOPDOWN_BULLET_1, 300, true
	);
}

void CCanon::Render()
{
	animation->RenderCenter(position.x, position.y);
	collisionBox->Render();
}
