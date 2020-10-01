#pragma once
#include "..\Constraints.h"
#include "..\Unit\Sprite.h"
#include <unordered_map>
#include <map>

//#define CAR_GUN_DOWNLEFT 1
//#define CAR_GUN_LEFT 2
//#define CAR_GUN_TOPLEFT 3
//#define CAR_GUN_TOP 4
//#define CAR_GUN_DOWNRIGHT 5
//#define CAR_GUN_RIGHT 6
//#define CAR_GUN_TOPRIGHT 7

using namespace std;

class CSpriteLibrary
{
private:
	static CSpriteLibrary* __instance;

	map<int, LPSprite> sprites;
public:
	static CSpriteLibrary* GetInstance();

	void Add(LPSprite sprite);
	LPSprite Get(unsigned int id);

	void DrawTest();
};

