#include "GameObject.h"
#include "../Graphic/Graphic.h"

void CGameObject::move(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

CGameObject::CGameObject(LPCWSTR texturePath)
{
	this->texture = CGraphic::Instance->LoadTexture(texturePath);
	x = 0;
	y = 0;
}

void CGameObject::SetPosition(float _x, float _y)
{
	x = _x;
	y = _y;
}

void CGameObject::Update(DWORD dt)
{
}

void CGameObject::Render()
{
	CGraphic::Instance->Draw(x, y, texture);
}

CGameObject::~CGameObject()
{
	//Free memory
	if (texture != NULL) texture->Release();
}
