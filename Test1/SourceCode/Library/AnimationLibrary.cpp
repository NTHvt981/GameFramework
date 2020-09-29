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
