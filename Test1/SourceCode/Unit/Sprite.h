#pragma once

#include "..\Constraints.h"
#include "../Graphic/Graphic.h"

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	Vector origin;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex
	, float origin_x = 0, float origin_y = 0);

	void Draw(float x, float y, int alpha = 255);
	void DrawWithFixedPosition(float x, float y, float alpha = 1);
	void Draw(Vector position, int alpha = 255);

	int GetId();
	void GetSize(int &width, int &height);
};

