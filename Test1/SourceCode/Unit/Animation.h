#pragma once
#include "../Constraints.h"
#include "../Library/AnimationLibrary.h"
#include "../Library/SpriteLibrary.h"
#include <vector>

#define ANIMATION_NORMAL 1
#define ANIMATION_PAUSE 0
#define ANIMATION_REVERSE -1

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
	int mode;
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPAnimationFrame> frames;
public:
	CAnimation(int id, int defaultTime, int mode=ANIMATION_NORMAL) { 
		this->id = id;
		this->defaultTime = defaultTime; 
		this->mode = mode;
		lastFrameTime = -1; 
		currentFrame = 0; 
	}
	void Add(int spriteId, DWORD time = 0);
	void Add(int spriteIds[], int size);
	void Render(float x, float y, int alpha = 255);
	void Render(Vector position, int alpha = 255);
	int GetId();
	LPAnimation Copy();

	int GetMode();
	void SetMode(int mode);
};

