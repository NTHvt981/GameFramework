#include "GameObject.h"
#include "../Graphic/Graphic.h"

void CGameObject::move(DWORD dt)
{
	position = position + velocity;
}

CGameObject::CGameObject(LPCWSTR texturePath)
{
	this->texture = CGraphic::Instance->LoadTexture(texturePath);
}

void CGameObject::SetPosition(float _x, float _y)
{
	position.x = _x;
	position.y = _y;
}

void CGameObject::Update(DWORD dt)
{
}

void CGameObject::Render()
{
	CGraphic::Instance->Draw(position, texture);
}

CGameObject::~CGameObject()
{
	//Free memory
	if (texture != NULL) texture->Release();
}
