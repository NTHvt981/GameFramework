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
	LPAnimation Get(unsigned int id);

	void DrawTest();
};

