#include "Sprite.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, 
	LPDIRECT3DTEXTURE9 tex
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
	CGraphic::Instance->Draw(texture, x, y, 
		left, top, right, bottom, origin.x, origin.y);
}

void CSprite::DrawWithFixedPosition(float x, float y, int alpha)
{
	CGraphic::Instance->DrawWithFixedPosition(texture, x, y,
		left, top, right, bottom);
}

void CSprite::Draw(Vector position, int alpha)
{
	Draw(position.x, position.y, alpha);
}

int CSprite::GetId()
{
	return id;
}
