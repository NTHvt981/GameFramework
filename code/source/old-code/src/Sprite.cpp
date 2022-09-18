#include "Sprite.h"

CSprite::CSprite(int64_t id, int64_t left, int64_t top, int64_t right, int64_t bottom, 
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

void CSprite::Draw(float x, float y, int64_t alpha)
{
	CGraphic::Instance->Draw(texture, x, y, 
		left, top, right, bottom, origin.x, origin.y);
}

void CSprite::DrawWithFixedPosition(float x, float y, float alpha)
{
	CGraphic::Instance->DrawWithFixedPosition(texture, x, y,
		left, top, right, bottom, alpha);
}

void CSprite::Draw(Vector position, int64_t alpha)
{
	Draw(position.x, position.y, alpha);
}

int64_t CSprite::GetId()
{
	return id;
}

void CSprite::GetSize(int64_t& width, int64_t& height)
{
	width = right - left;
	height = bottom - top;
}

