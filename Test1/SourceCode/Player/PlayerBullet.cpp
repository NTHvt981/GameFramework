#include "PlayerBullet.h"

CPlayerBullet::CPlayerBullet(Vector direction): CEntity() {
	SetType(GOTYPES::PlayerBullet);
	selfDestructTimer = new CTimer(75);
	selfDestructTimer->Start();

	Vector size = Vector(20, 6);
	int sprId;

	if (direction.x == 1)
	{
		sprId = ID_CAR_BULLET_RIGHT;
		velocity = Vector(speed, 0);
	}
	else if (direction.x == -1)
	{
		sprId = ID_CAR_BULLET_LEFT;
		velocity = Vector(-speed, 0);
	}
	else
	{
		if (direction.y == -1)
		{
			sprId = ID_CAR_BULLET_UP;
			velocity = Vector(0, -speed);

			//swap size w and h of coli box
			int temp = size.x;
			size.x = size.y;
			size.y = temp;
		}
	}

	collisionBox = new CDynamicBox(
		this, 0, 0, size.x, size.y
	);
	collisionBox->SetSolid(false);

	sprite = CSpriteLibrary::GetInstance()->Get(sprId);

	//DebugOut(L"[INFO] CREATE BULLET\n");
}

void CPlayerBullet::Update(DWORD dt)
{
	bool delete_condition = false;
	old_velocity.Set(velocity.x, velocity.y);

	move(dt);
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

		dynamic_cast<LPEntity>(ls.front())->InflictDamage(damage);

		delete_condition = true;
	}

	if (delete_condition)
	{
		LPRequest request = new CGameRequest(REQUEST_TYPES::DeleteEntity);
		request->id = this->id;
		CGame::GetInstance()->AddRequest(request);
	}
}

void CPlayerBullet::Render()
{
	sprite->Draw(position);
	collisionBox->Render();
}
