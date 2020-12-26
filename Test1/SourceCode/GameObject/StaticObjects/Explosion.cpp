#include "Explosion.h"

CExplosion::CExplosion(EXPLOSION_TYPES type): CEntity() {
	animation = new CAnimation(100, 1, false);

	switch (type) {
	case EXPLOSION_TYPES::Big:
		animation->Add(ID_EXPLOSION_4);
	case EXPLOSION_TYPES::Medium:
		animation->Add(ID_EXPLOSION_3);
	case EXPLOSION_TYPES::Small:
		animation->Add(ID_EXPLOSION_2);
		animation->Add(ID_EXPLOSION_1);
		break;
	}

	collisionBox = new CDynamicBox(
		this, -5, -5, 10, 10
	);
	collisionBox->SetSolid(false);
}

void CExplosion::Update(DWORD dt)
{
	if (animation->IsEnd())
	{
		CSceneRequest* req = new CSceneRequest(SCENE_REQUEST_TYPES::DeleteEntity);
		req->id = id;
		CSceneRequest::AddRequest(req);
	}
}

void CExplosion::Move(DWORD dt)
{
}

void CExplosion::Render()
{
	animation->RenderCenter(position.x, position.y);
	//collisionBox->Render();
}

void CExplosion::CreateExplosion(float x, float y, EXPLOSION_TYPES type)
{
	CSceneRequest* req = new CSceneRequest(SCENE_REQUEST_TYPES::CreateEntity);

	req->entity = new CExplosion(type);
	req->x = x;
	req->y = y;

	CSceneRequest::AddRequest(req);
}
