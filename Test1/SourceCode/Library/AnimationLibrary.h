#pragma once

#include "../Constraints.h"
#include "../Unit/Animation.h"
#include <map>

using namespace std;

class CAnimationLibrary
{
private:
	static CAnimationLibrary* __instance;

	map<int, LPAnimation> animations;
public:
	static CAnimationLibrary* GetInstance();

	void Add(LPAnimation anim);
	void Add(LPAnimation anim, int id);
	LPAnimation Get(unsigned int id);

	void DrawTest();
};

