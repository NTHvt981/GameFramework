#include "SpiralBullet.h"

CSpiralBullet::CSpiralBullet(
	Vector _pivot, int _spriteId, int selfDestructTime
) :CEnemyBullet(Vector(0, 0), 0, 0, _spriteId, selfDestructTime, true)
{
	velocity.Set(0, 0);
	pivot.Set(_pivot.x, _pivot.y);
}

void CSpiralBullet::Update(DWORD dt)
{
	CEnemyBullet::Update(dt);
}

void CSpiralBullet::SetLength(float _length)
{
	length = _length;
}

void CSpiralBullet::Create(
	float x, float y, Vector _pivot, int _spriteId, int selfDestructTime)
{
	LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::CreateEntity);
	CSpiralBullet* bullet = new CSpiralBullet(
		_pivot, _spriteId, selfDestructTime
	);

	bullet->SetLength(Vector(x - _pivot.x, y - _pivot.y).Length());

	request->entity = bullet;
	request->x = x; request->y = y;
	CSceneRequest::AddRequest(request);
}

void CSpiralBullet::Move(DWORD dt)
{
	Vector center = GetCenter();
	Vector distance = Vector(center.x - pivot.x, center.y - pivot.y);
	
	float _x = distance.x / length;
	float _y = distance.y / length;

	if (_x == 1)
		if (_y != 0)
			_x = 1 - _y;

	if (_x == 1)
		if (_y != 0)
			_x = 1 - _y;

	Vector circularVel, otherVel;
	circularVel.Set(_y * circularSpeed, -_x * circularSpeed);
	otherVel.Set(_x * speed, _y * speed);
	//otherVel.Set(0, 0);
	
	velocity.Set(circularVel.x + otherVel.x, circularVel.y + otherVel.y);
	CEnemyBullet::MoveWithoutGravity(dt);
}
