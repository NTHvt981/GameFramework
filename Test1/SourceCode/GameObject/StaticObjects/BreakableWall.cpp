#include "BreakableWall.h"

void CBreakableWall::Move(DWORD dt)
{
}

void CBreakableWall::SetPosition(float _x, float _y)
{

}

CBreakableWall::CBreakableWall(float l, float t, float r, float b) : CEntity()
{
	sprite = CSpriteLibrary::GetInstance()->Get(ID_BREAKABLE_WALL);

	position = Vector(-1, -1);
	velocity = Vector(0, 0);

	collisionBox = new CDynamicBox(this);
	collisionBox->SetLTRB(l, t, r, b);
	collisionBox->SetSolid(true);

	SetType(GOTYPES::BreakableWall);

	left = l;
	top = t;
}

void CBreakableWall::Update(DWORD dt)
{

}

void CBreakableWall::Render()
{
	sprite->Draw(left, top);
	collisionBox->Render();
}

void CBreakableWall::Destroy()
{
	CGameRequest* req = new CGameRequest(REQUEST_TYPES::DeleteEntity);

	req->id = this->GetId();
	CGameRequest::AddRequest(req);
}