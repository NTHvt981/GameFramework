#include "Mine.h"

CMine::CMine(): CEnemy()
{
	gravity = 3;
}

void CMine::Update(DWORD dt)
{
	if (!IsCollidedWith(GOTYPES::Wall))
		Move(dt);

	CPlayer* player = CPlayer::GetCurrentPlayer();
	if (IsColliding(player))
		Explode();
}

void CMine::Render()
{
}

void CMine::Explode()
{
	LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::DeleteEntity);
	request->id = this->id;
	CSceneRequest::AddRequest(request);

	Vector center = GetCenter();

	if (CUtils::lottery(HEALTH_PICKUP_CHANCE))
	{
		LPSceneRequest pickupReq = new CSceneRequest(SCENE_REQUEST_TYPES::CreateHealthBall);
		pickupReq->x = center.x;
		pickupReq->y = center.y;
		CSceneRequest::AddRequest(pickupReq);
	}

	CExplosion::CreateExplosion(center.x, center.y, EXPLOSION_TYPES::Big);
}
