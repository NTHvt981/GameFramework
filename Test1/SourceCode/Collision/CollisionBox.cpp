#include "CollisionBox.h"

int CCollisionBox::countId = 0;

CCollisionBox::CCollisionBox(LPGameObject obj, float l, float t, float r, float b)
{
	//Set id
	id = countId;
	countId++;

	left = l;
	top = t;
	right = r;
	bottom = b;

	owner = obj;

	CCollision::GetInstance()->AddCollisionBox(this);
}

void CCollisionBox::RemoveCoBox(LPCollisionBox lpBox)
{
	try
	{
		coCollisionBoxes.remove(lpBox);
	}
	catch (const std::exception& ex)
	{
		DebugOut(L"[ERROR] remove collision box, exception code %s", *ex.what());
	}
}

void CCollisionBox::AddCoBox(LPCollisionBox lpBox)
{
	coCollisionBoxes.push_back(lpBox);
}

void CCollisionBox::Render()
{
	D3DXVECTOR3 position(
		left, top, 0);
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

int CCollisionBox::GetId()
{
	return id;
}

void CCollisionBox::GetCollision(list<CollisionEvent>& events)
{
	events.clear();
	CCollision::GetInstance()->GetCollisionBoxes(id, coCollisionBoxes);

	for each (LPCollisionBox staticBox in coCollisionBoxes)
	{
		//get left, top, right, bottom of other collision boxes
		float staticLeft, staticTop, staticRight, staticBottom;
		staticLeft = staticBox->GetLeft();
		staticTop = staticBox->GetTop();
		staticRight = staticBox->GetRight();
		staticBottom = staticBox->GetBottom();

		//if false -> garantee no Collision
		if (AABBCheck(
			left, top, right, bottom,
			staticLeft, staticTop, staticRight, staticBottom
		))
		{
			events.push_back({ staticBox->GetOwner(), Vector(0, 0) });
		}
	}
}

void CCollisionBox::IsColliding(LPCollisionBox box, bool& result)
{
	//get left, top, right, bottom of other collision boxes
	float staticLeft, staticTop, staticRight, staticBottom;
	staticLeft = box->GetLeft();
	staticTop = box->GetTop();
	staticRight = box->GetRight();
	staticBottom = box->GetBottom();

	//if false -> garantee no Collision
	result = AABBCheck(
		left, top, right, bottom,
		staticLeft, staticTop, staticRight, staticBottom
	);
}

void CCollisionBox::SetLTRB(float l, float t, float r, float b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}

void CCollisionBox::GetLTRB(float &l, float &t, float &r, float &b)
{
	l = left;
	t = top;
	r = right;
	b = bottom;
}

void CCollisionBox::SetSolid(bool _solid)
{
	this->solid = _solid;
}

bool CheckCollision(LPCollisionBox a, LPCollisionBox b)
{
	float al, at, ar, ab;
	float bl, bt, br, bb;

	a->GetLTRB(al, at, ar, ab);
	b->GetLTRB(bl, bt, br, bb);

	return AABBCheck(al, at, ar, ab, bl, bt, br, bb);
}
