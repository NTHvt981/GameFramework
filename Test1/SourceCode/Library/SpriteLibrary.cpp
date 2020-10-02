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

void CSpriteLibrary::Add(int id, int l, int t, int r, int b, LPDIRECT3DTEXTURE9 tex)
{
	LPSprite spr = new CSprite(id, l, t, r, b, tex);
	Add(spr);
}

LPSprite CSpriteLibrary::Get(unsigned int id)
{
	return sprites[id];
}

void CSpriteLibrary::DrawTest()
{
	float x = 100;
	float y = 100;
	for each (pair<int, LPSprite> it in sprites)
	{
		if (x < WINDOW_WIDTH)
			x += 100;
		else
		{
			x = 100;
			y += 100;
		}
		it.second->Draw(x, y);
	}
}
