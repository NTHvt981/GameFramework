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

void CAnimation::SelfSetCurrentFrame()
{
	DWORD now = GetTickCount();
	if (lastFrameTime == -1) lastFrameTime = now;

	DWORD t = frames[currentFrame]->GetTime();
	if ((now - lastFrameTime) * speed > t)
	{
		currentFrame = currentFrame + mode;
		lastFrameTime = now;
	}

	//check to see if current frame out of frames limit
	if (currentFrame == -1)
		currentFrame = frames.size() - 1;
	else if (currentFrame == frames.size()) {
		currentFrame = 0;

		if (!loop) {
			currentFrame = frames.size() - 1;
			end = true;
		}
	}
}

void CAnimation::Render(float x, float y, int alpha)
{
	SelfSetCurrentFrame();

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

void CAnimation::RenderCenter(float x, float y, int alpha)
{
	SelfSetCurrentFrame();

	int w, h;
	frames[currentFrame]->GetSprite()->GetSize(w, h);

	frames[currentFrame]->GetSprite()->Draw(x - w/2, y - h/2, alpha);
}

void CAnimation::Render(Vector position, int alpha)
{
	Render(position.x, position.y, alpha);
}

void CAnimation::RenderWithFixedPosition(float x, float y, int alpha)
{
	SelfSetCurrentFrame();

	frames[currentFrame]->GetSprite()->DrawWithFixedPosition(x, y, alpha);
}

bool CAnimation::IsLoop()
{
	return loop;
}

bool CAnimation::IsEnd()
{
	return end;
}

void CAnimation::Reset()
{
	currentFrame = 0;
	end = false;
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

int CAnimation::GetCurrentFrame()
{
	return currentFrame;
}

void CAnimation::SetCurrentFrame(int fr)
{
	currentFrame = fr;
	lastFrameTime = 0;
}

void CAnimation::GetSize(int& width, int& height)
{
	frames[0]->GetSprite()->GetSize(width, height);
}

void CAnimation::SetSpeed(float _speed)
{
	speed = _speed;
}

float CAnimation::GetSpeed()
{
	return speed;
}
