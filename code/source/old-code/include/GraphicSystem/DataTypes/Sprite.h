#pragma once

#include "Constraints.h"
#include "Graphic.h"

class CSprite
{
	int64_t id;				// Sprite ID in the spriteRef database

	int64_t left;
	int64_t top;
	int64_t right;
	int64_t bottom;

	Vector origin;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int64_t id, int64_t left, int64_t top, int64_t right, int64_t bottom, LPDIRECT3DTEXTURE9 tex
	, float origin_x = 0, float origin_y = 0);

	void Draw(float x, float y, int64_t alpha = 255);
	void DrawWithFixedPosition(float x, float y, float alpha = 1);
	void Draw(Vector position, int64_t alpha = 255);

	int64_t GetId();
	void GetSize(int64_t &width, int64_t &height);
};

