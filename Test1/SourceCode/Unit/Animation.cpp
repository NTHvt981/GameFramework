#include "Animation.h"

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSprite sprite = CSpriteLibrary::GetInstance()->Get(spriteId);
	LPAnimationFrame frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Add(int spriteIds[], int size)
{
	for (int i = 0; i < size; i++)
	{
		Add(spriteIds[i]);
	}
}

void CAnimation::Render(float x, float y)
{
	DWORD now = GetTickCount();
	if (lastFrameTime == -1) lastFrameTime = now;

	DWORD t = frames[currentFrame]->GetTime();
	if (now - lastFrameTime > t)
	{
		currentFrame = currentFrame + mode;
		lastFrameTime = now;
	}

	//check to see if current frame out of frames limit
	if (currentFrame == -1)
		currentFrame = frames.size() - 1;
	else if (currentFrame == frames.size()) currentFrame = 0;

	frames[currentFrame]->GetSprite()->Draw(x, y);
}

int CAnimation::GetId()
{
	return id;
}

LPAnimation CAnimation::Copy()
{
	return new CAnimation(*this);
}

int CAnimation::GetMode()
{
	return mode;
}

void CAnimation::SetMode(int _mode)
{
	this->mode = _mode;
}
