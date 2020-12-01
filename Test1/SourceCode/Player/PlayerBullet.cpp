#include "PlayerBullet.h"

CPlayerBullet::CPlayerBullet(Vector direction): CEntity() {
	SetType(GOTYPES::PlayerBullet);
	selfDestructTimer = new CTimer(75);
	selfDestructTimer->Start();
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
		list<LPGameObject> ls;
		GetCollidedWith(GOTYPES::Enemy, ls);

		dynamic_cast<LPEnemy>(ls.front())->InflictDamage(damage);

		delete_condition = true;
	}	
	
	if (IsCollidedWith(GOTYPES::BreakableWall))
	{
		list<LPGameObject> ls;
		GetCollidedWith(GOTYPES::BreakableWall, ls);

		dynamic_cast<CBreakableWall*>(ls.front())->Destroy();

		delete_condition = true;
	}

	if (delete_condition)
	{
		LPRequest request = new CGameRequest(REQUEST_TYPES::DeleteEntity);
		request->id = this->id;
		CGameRequest::AddRequest(request);
	}
}

void CPlayerBullet::Render()
{
	sprite->Draw(position);
	collisionBox->Render();
}
