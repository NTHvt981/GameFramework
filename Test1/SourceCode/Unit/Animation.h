#pragma once
#include "../Constraints.h"
#include "../Library/AnimationLibrary.h"
#include "../Library/SpriteLibrary.h"
#include <vector>

using namespace std;

class CAnimationFrame
{
	LPSprite sprite;
	DWORD time;

public:
	CAnimationFrame(LPSprite sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSprite GetSprite() { return sprite; }
};

class CAnimation
{
	int id;
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPAnimationFrame> frames;
public:
	CAnimation(int id, int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y);
	int GetId();
};

