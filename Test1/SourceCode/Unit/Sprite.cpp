#include "Sprite.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex
	, float origin_x, float origin_y) {
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;

	this->origin.x = origin_x;
	this->origin.y = origin_y;
}

void CSprite::Draw(float x, float y, int alpha)
{
	CGraphic::Instance->Draw(x, y, texture, left, top, right, bottom, origin.x, origin.y);
}

int CSprite::GetId()
{
	return id;
}
