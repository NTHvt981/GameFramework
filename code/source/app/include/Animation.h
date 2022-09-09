#pragma once
#include "Constraints.h"
#include "SpriteLibrary.h"
#include <vector>

#define ANIMATION_NORMAL 1
#define ANIMATION_PAUSE 0
#define ANIMATION_REVERSE -1



class CAnimationFrame
{
	LPSprite sprite;
	DWORD time;

public:
	CAnimationFrame(LPSprite sprite, int64_t time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSprite GetSprite() { return sprite; }
};

class CAnimation
{
	int64_t mode;
	DWORD lastFrameTime;
	int64_t defaultTime;
	int64_t currentFrame;
	std::vector<LPAnimationFrame> frames;

	bool loop;
	bool end = false;
	float speed = 1;

private:
	void SelfSetCurrentFrame();

public:
	CAnimation(int64_t defaultTime, int64_t mode=ANIMATION_NORMAL, bool loop=true) { 
		this->defaultTime = defaultTime; 
		this->mode = mode;
		this->loop = loop;
		lastFrameTime = -1; 
		currentFrame = 0; 
	}
	void Add(int64_t spriteId, DWORD time = 0);
	void Add(int64_t spriteIds[], int64_t size);
	void Render(float x, float y, int64_t alpha = 255);
	void RenderCenter(float x, float y, int64_t alpha = 255);
	void Render(Vector position, int64_t alpha = 255);
	void RenderWithFixedPosition(float x, float y, int64_t alpha = 255);
	int64_t GetId();
	bool IsLoop();
	bool IsEnd();
	void Reset();
	
	LPAnimation Copy();

	int64_t GetMode();
	void SetMode(int64_t mode);

	int64_t GetCurrentFrame();
	void SetCurrentFrame(int64_t fr);

	void GetSize(int64_t&width, int64_t&height);

	void SetSpeed(float _speed);
	float GetSpeed();
};

