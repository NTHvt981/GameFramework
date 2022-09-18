#include "EnemyBullet.h"

CEnemyBullet::CEnemyBullet(
	Vector _direction,
	float _speed,
	float _gravity = 0,
	int64_t _spriteId = ID_SKULL_BULLET,
	int64_t _selfDestructTime = -1,
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
	collisionBox = new CDynamicBox(
		this, 0, 0,
		width, height
	);
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
	bool con3 = false;

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

	con3 = IsColliding(CPlayer::GetCurrentPlayer());

	if (con1 || con2 || con3)
	{
		SelfDestruct();
	}
}

void CEnemyBullet::Render()
{
	sprite->Draw(position);
	collisionBox->Render();
}

void CEnemyBullet::Create(float x, float y,
	Vector _direction, float _speed, float _gravity, 
	int64_t _spriteId, int64_t selfDestructTime, 
	bool _useSolid)
{
	LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::CreateEntity);
	request->entity = new CEnemyBullet(
		_direction, _speed, _gravity, _spriteId, selfDestructTime, _useSolid
		);
	request->x = x; request->y = y;
	CSceneRequest::AddRequest(request);
}

void CEnemyBullet::SelfDestruct()
{
	LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::DeleteEntity);
	request->id = this->id;
	CSceneRequest::AddRequest(request);

	const float length = velocity.Length();
	const Vector center = GetCenter();
	CExplosion::CreateExplosion(
		center.x + (velocity.x / length) * width / 2,
		center.y + (velocity.y / length) * height / 2,
		EXPLOSION_TYPES::Small);
}
