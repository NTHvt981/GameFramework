#include "EnemyBullet.h"

CEnemyBullet::CEnemyBullet(
	Vector _direction,
	float _speed,
	float _gravity = 0,
	int _spriteId = ID_SKULL_BULLET,
	int _selfDestructTime = -1,
	bool _useSolid = false
)
{
	SetType(GOTYPES::EnemyBullet);

	float dirLength = _direction.Length();

	direction.x = _direction.x / dirLength;
	direction.y = _direction.y / dirLength;

	velocity.x = direction.x * _speed;
	velocity.y = direction.y * _speed;

	gravity = _gravity;

	sprite = CSpriteLibrary::GetInstance()->Get(_spriteId);
	sprite->GetSize(width, height);
	collisionBox = new CDynamicBox(this, 0, 0, width, height);
	collisionBox->SetSolid(false);

	if (_selfDestructTime == -1)
	{
		useTimer = false;
	}
	selfDestructTime = _selfDestructTime;

	useSolid = _useSolid;
}

void CEnemyBullet::Update(DWORD dt)
{
	Move(dt);
	
	bool con1 = false;
	bool con2 = false;
	if (useTimer)
	{
		countUp += dt;
		if (countUp >= selfDestructTime)
			con1 = true;
	}

	if (useSolid)
		if (collisionBox->IsHypothesizedColliding(
			position.x + velocity.x, position.y + velocity.y
		))
			con2 = true;

	if (con1 || con2)
	{
		LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::DeleteEntity);
		request->id = this->id;
		CSceneRequest::AddRequest(request);

		CExplosion::CreateExplosion(GetCenter().x, GetCenter().y, EXPLOSION_TYPES::Small);
	}
}

void CEnemyBullet::Render()
{
	sprite->Draw(position);
	collisionBox->Render();
}
