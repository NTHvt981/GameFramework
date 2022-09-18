#include "SpriteLibrary.h"

CSpriteLibrary* CSpriteLibrary::__instance = NULL;

CSpriteLibrary* CSpriteLibrary::GetInstance()
{
	if (__instance == NULL) __instance = new CSpriteLibrary();
	return __instance;
}

void CSpriteLibrary::Add(LPSprite sprite)
{
	sprites[sprite->GetId()] = sprite;
}

void CSpriteLibrary::Add(int64_t id, int64_t l, int64_t t, int64_t r, int64_t b, 
	LPDIRECT3DTEXTURE9 tex, float origin_x, float origin_y)
{
	LPSprite spr = new CSprite(id, l, t, r, b, tex, origin_x, origin_y);
	Add(spr);
}

LPSprite CSpriteLibrary::Get(uint64_t id)
{
	return sprites[id];
}

void CSpriteLibrary::DrawTest()
{
	float x = 100;
	float y = 100;
	for (std::pair<int64_t, LPSprite> it: sprites)
	{
		if (x < CAMERA_WIDTH)
			x += 100;
		else
		{
			x = 100;
			y += 100;
		}
		it.second->Draw(x, y);
	}
}
