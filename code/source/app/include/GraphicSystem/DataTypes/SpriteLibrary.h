#pragma once
#include "Constraints.h"
#include "Sprite.h"
#include <unordered_map>
#include <map>



class CSpriteLibrary
{
private:
	static CSpriteLibrary* __instance;

	std::map<int64_t, LPSprite> sprites;
public:
	static CSpriteLibrary* GetInstance();

	void Add(LPSprite sprite);
	void Add(int64_t id, int64_t l, int64_t t, int64_t r, int64_t b,
		LPDIRECT3DTEXTURE9 tex, float origin_x=0, float origin_y=0);
	LPSprite Get(uint64_t id);

	void DrawTest();
};

