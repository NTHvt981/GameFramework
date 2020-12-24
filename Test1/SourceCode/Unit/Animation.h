#pragma once
#include "../Constraints.h"
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
	int mode;
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPAnimationFrame> frames;

	bool loop;
	bool end = false;
	float speed = 1;

private:
	void SelfSetCurrentFrame();

public:
	CAnimation(int defaultTime, int mode=ANIMATION_NORMAL, bool loop=true) { 
		this->defaultTime = defaultTime; 
		this->mode = mode;
		this->loop = loop;
		lastFrameTime = -1; 
		currentFrame = 0; 
	}
	void Add(int spriteId, DWORD time = 0);
	void Add(int spriteIds[], int size);
	void Render(float x, float y, int alpha = 255);
	void RenderCenter(float x, float y, int alpha = 255);
	void Render(Vector position, int alpha = 255);
	void RenderWithFixedPosition(float x, float y, int alpha = 255);
	int GetId();
	bool IsLoop();
	bool IsEnd();
	void Reset();
	
	LPAnimation Copy();

	int GetMode();
	void SetMode(int mode);

	int GetCurrentFrame();
	void SetCurrentFrame(int fr);

	void GetSize(int&width, int&height);

	void SetSpeed(float _speed);
	float GetSpeed();
};

