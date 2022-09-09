#include "PlayerBullet.h"

CPlayerBullet::CPlayerBullet(Vector direction): CEntity() {
	SetType(GOTYPES::PlayerBullet);
	selfDestructTimer = new CTimer(75);
	selfDestructTimer->Start();
}

void CPlayerBullet::CreateEffect(float vx, float vy)
{
	float size_x, size_y, dir_x, dir_y, pos_x, pos_y;

	Vector pos = GetCenter();
	Vector size = collisionBox->GetSize();

	pos_x = pos.x;
	pos_y = pos.y;

	size_x = size.x;
	size_y = size.y;

	if (vx == 0) dir_x = 0;
	if (vx > 0) dir_x = 1;
	if (vx < 0) dir_x = -1;

	if (vy == 0) dir_y = 0;
	if (vy > 0) dir_y = 1;
	if (vy < 0) dir_y = -1;

	CExplosion::CreateExplosion(
		pos_x + dir_x * size_x / 2,
		pos_y + dir_y * size_y / 2,
		effectType
	);
}

void CPlayerBullet::Update(DWORD dt)
{
	bool delete_condition = false;
	old_velocity.Set(velocity.x, velocity.y);

	Move(dt);
	collisionBox->Update();

	/// <summary>
	/// self destruct in 3 conditions
	/// 1 - time is out
	/// 2 - touch wall
	/// 3 - touch enemy (also inflict damage)
	/// </summary>

	//condition 1
	selfDestructTimer->Update(dt);
	if (selfDestructTimer->JustFinish())
		delete_condition = true;

	//condition 2
	if (
		(velocity.x == 0 && velocity.y == 0) &&
		(old_velocity.x != 0 || old_velocity.y != 0)
		)
		delete_condition = true;

	if (IsCollidedWith(GOTYPES::Enemy))
	{
		std::list<LPGameObject> ls;
		GetCollidedWith(GOTYPES::Enemy, ls);

		dynamic_cast<LPEnemy>(ls.front())->InflictDamage(damage);

		delete_condition = true;
	}	
	
	if (IsCollidedWith(GOTYPES::BreakableWall))
	{
		std::list<LPGameObject> ls;
		GetCollidedWith(GOTYPES::BreakableWall, ls);

		dynamic_cast<CBreakableWall*>(ls.front())->Destroy();

		delete_condition = true;
	}

	if (delete_condition)
	{
		LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::DeleteEntity);
		request->id = this->id;
		CSceneRequest::AddRequest(request);

		CreateEffect(old_velocity.x, old_velocity.y);
	}
}

void CPlayerBullet::Render()
{
	sprite->Draw(position);
	collisionBox->Render();
}
