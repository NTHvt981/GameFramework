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
	if (health == 0)
	{
		LPRequest request = new CGameRequest(REQUEST_TYPES::DeleteEntity);
		request->id = this->id;
		CGameRequest::AddRequest(request);
	}
}

void CEnemy::InflictDamage(int dam)
{
	health = max(0, health - dam);
}