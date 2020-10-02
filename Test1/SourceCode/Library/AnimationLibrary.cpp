#include "AnimationLibrary.h"

CAnimationLibrary* CAnimationLibrary::__instance = NULL;

CAnimationLibrary* CAnimationLibrary::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimationLibrary();
	return __instance;
}

void CAnimationLibrary::Add(LPAnimation anim)
{
	animations[anim->GetId()] = anim;
}

void CAnimationLibrary::Add(LPAnimation anim, int id)
{
	animations[id] = anim;
}

LPAnimation CAnimationLibrary::Get(unsigned int id)
{
	return animations[id];
}

void CAnimationLibrary::DrawTest()
{
	float x = 50;
	float y = 50;
	for each (pair<int, LPAnimation> it in animations)
	{
		if (x < WINDOW_WIDTH)
			x += 15;
		else
		{
			x = 50;
			y += 100;
		}
		it.second->Render(x, y);
	}
}
