#include "Enemy.h"

void CEnemy::SetMaxHealth(int mh) {
	maxHealth = mh;
	health = mh;
}

CEnemy::CEnemy()
{
	SetMaxHealth(1);
	SetType(GOTYPES::Enemy);
}

void CEnemy::Update(DWORD dt)
{
}

void CEnemy::InflictDamage(int dam)
{
	health = max(0, health - dam);

	if (health == 0)
	{
		LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::DeleteEntity);
		request->id = this->id;
		CSceneRequest::AddRequest(request);

		if (CUtils::lottery(HEALTH_PICKUP_CHANCE))
		{
			LPSceneRequest pickupReq = new CSceneRequest(SCENE_REQUEST_TYPES::CreateHealthBall);
			pickupReq->x = GetCenter().x;
			pickupReq->y = GetCenter().y;
			CSceneRequest::AddRequest(pickupReq);
		}

		CExplosion::CreateExplosion(GetCenter().x, GetCenter().y, EXPLOSION_TYPES::Big);
	}
}

float CEnemy::DistanceToPlayer()
{
	Vector playerPos = CPlayer::GetCurrentPlayer()->GetCenter();
	Vector selfPos = GetCenter();

	float result = sqrt(
		pow(playerPos.x - selfPos.x, 2) +
		pow(playerPos.y - selfPos.y, 2)
	);

	return result;
}

float CEnemy::HorizontalDistanceToPlayer()
{
	Vector playerPos = CPlayer::GetCurrentPlayer()->GetCenter();
	Vector selfPos = GetCenter();

	return abs(playerPos.x - selfPos.x);
}

float CEnemy::VerticalDistanceToPlayer()
{
	Vector playerPos = CPlayer::GetCurrentPlayer()->GetCenter();
	Vector selfPos = GetCenter();

	return abs(playerPos.y - selfPos.y);
}
