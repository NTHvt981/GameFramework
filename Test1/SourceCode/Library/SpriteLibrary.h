#pragma once
#include "..\Constraints.h"
#include "..\Unit\Sprite.h"
#include <unordered_map>
#include <map>

using namespace std;

class CSpriteLibrary
{
private:
	static CSpriteLibrary* __instance;

	map<int, LPSprite> sprites;
public:
	static CSpriteLibrary* GetInstance();

	void Add(LPSprite sprite);
	void Add(int id, int l, int t, int r, int b,
		LPDIRECT3DTEXTURE9 tex, float origin_x=0, float origin_y=0);
	LPSprite Get(unsigned int id);

	void DrawTest();
};

