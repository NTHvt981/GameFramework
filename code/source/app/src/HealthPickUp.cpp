#include "HealthPickUp.h"

CHealthPickUp::CHealthPickUp(): CPickUp()
{
	sprite = CSpriteLibrary::GetInstance()->Get(ID_HEALTH_BALL);
}

void CHealthPickUp::InContactWithPlayer()
{
	CPlayerHealth::GetInstance()->IncreaseHealth(HEALTH_INCREASE);
}
