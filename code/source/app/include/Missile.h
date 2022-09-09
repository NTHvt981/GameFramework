#pragma once

#include "Constraints.h"
#include "Entity.h"
#include "SpriteLibrary.h"
#include "SceneRequest.h"
#include "Enemy.h"

#define MISSILE_SEARCH_RANGE 200
#define MISSILE_DAMAGE 5
#define MISSILE_SEARCH 0
#define MISSILE_CHASE 1
#define MISSILE_SPEED 2

class CMissileSearcher: public CEntity {
public:
	void Follow(float x, float y);
	std::list<LPEntity> GetTargets();

public:
	CMissileSearcher();
	void Update(DWORD dt);
	void Render();
};

class CMissile: public CEntity
{
private:
	CMissileSearcher* searcher;
	LPEntity target = NULL;
	int64_t state = MISSILE_SEARCH;

	LPSprite head;
	LPSprite headLeft;
	LPSprite headUp;
	LPSprite headRight;
	LPSprite headDown;

	LPSprite tail;
	LPSprite tailLeft;
	LPSprite tailUp;
	LPSprite tailRight;
	LPSprite tailDown;

	Vector* tailPos;
	Vector tailPosLeft = Vector(8, 0);
	Vector tailPosUp = Vector(0, 8);
	Vector tailPosRight = Vector(-8, 0);
	Vector tailPosDown = Vector(0, -8);

	int64_t headWidth, headHeight;
	int64_t tailWidth, tailHeight;

	Vector direction;

	DWORD countUp = 0;
	const DWORD waitTime = 600;

public:
	CMissile(CMissileSearcher *s, float dir_x=0, float dir_y=-1);
	void Update(DWORD dt);
	void Render();

public:
	void SearchState(DWORD dt);
	void ChaseState(DWORD dt);
	void SetSprites();

private:
	void CreateEffect(float vx, float vy);
	void SelfDestroy();
};

