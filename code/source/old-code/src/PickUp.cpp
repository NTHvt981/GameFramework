#include "PickUp.h"

void CPickUp::InContactWithPlayer()
{
}

CPickUp::CPickUp() : CEntity()
{
	collisionBox = new CDynamicBox(
		this,
		-width / 2, -height / 2,
		width, height
	);
	collisionBox->SetSolid(false);

	SetType(GOTYPES::Dynamic);
}

void CPickUp::Update(DWORD dt)
{
	if (IsColliding(CPlayer::GetCurrentPlayer()))
	{
		InContactWithPlayer();

		CSceneRequest* req = new CSceneRequest(SCENE_REQUEST_TYPES::DeleteEntity);
		req->id = id;
		CSceneRequest::AddRequest(req);
	}
}

void CPickUp::Render()
{
	sprite->Draw(position.x - width / 2, position.y - height / 2);
	collisionBox->Render();
}
