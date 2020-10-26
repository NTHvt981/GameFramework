#include "CollisionBox.h"

CCollisionBox::CCollisionBox(LPGameObject obj, float l, float t, float r, float b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;

	owner = obj;

	for each (LPCollisionBox box in CCollision::GetInstance()->GetCollisionBoxes())
	{
		collisionBoxes.push_back(box);
		box->AddCoBox(this);
	}
	CCollision::GetInstance()->AddCollisionBox(this);
}

void CCollisionBox::RemoveCoBox(LPCollisionBox lpBox)
{
	try
	{
		collisionBoxes.remove(lpBox);
	}
	catch (const std::exception& ex)
	{
		DebugOut(L"[ERROR] remove collision box, exception code %s", *ex.what());
	}
}

void CCollisionBox::AddCoBox(LPCollisionBox lpBox)
{
	collisionBoxes.push_back(lpBox);
}

void CCollisionBox::Render()
{
	D3DXVECTOR3 position(
		left, bottom, 0);
	D3DXVECTOR3 origin(0, 0, 0);

	LPDIRECT3DTEXTURE9 bbox = CTextureLibrary::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;
	l = 0;
	t = 0;
	r = right - left;
	b = bottom- top;

	CGraphic::Instance->Draw(bbox, position.x, position.y, l, t, r, b, 0, 0, 0.2);
}

float CCollisionBox::GetLeft()
{
	return left;
}

float CCollisionBox::GetTop()
{
	return top;
}

float CCollisionBox::GetRight()
{
	return right;
}

float CCollisionBox::GetBottom()
{
	return bottom;
}

LPGameObject CCollisionBox::GetOwner()
{
	return owner;
}

bool CCollisionBox::IsSolid()
{
	return solid;
}

void CCollisionBox::GetCollision(list<LPGameObject>& objectsCollide)
{
	// TODO: i will add this later
}

void CCollisionBox::SetLTRB(float l, float t, float r, float b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}

void CCollisionBox::SetSolid(bool _solid)
{
	this->solid = _solid;
}
