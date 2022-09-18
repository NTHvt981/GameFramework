#include "Animation.h"

void CAnimation::Add(int64_t spriteId, DWORD time)
{
	int64_t t = time;
	if (time == 0) t = this->defaultTime;

	LPSprite sprite = CSpriteLibrary::GetInstance()->Get(spriteId);
	LPAnimationFrame frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Add(int64_t spriteIds[], int64_t size)
{
	for (int64_t i = 0; i < size; i++)
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

void CAnimation::Render(float x, float y, int64_t alpha)
{
	SelfSetCurrentFrame();

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

void CAnimation::RenderCenter(float x, float y, int64_t alpha)
{
	SelfSetCurrentFrame();

	int64_t w, h;
	frames[currentFrame]->GetSprite()->GetSize(w, h);

	frames[currentFrame]->GetSprite()->Draw(x - w/2, y - h/2, alpha);
}

void CAnimation::Render(Vector position, int64_t alpha)
{
	Render(position.x, position.y, alpha);
}

void CAnimation::RenderWithFixedPosition(float x, float y, int64_t alpha)
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

int64_t CAnimation::GetMode()
{
	return mode;
}

void CAnimation::SetMode(int64_t _mode)
{
	this->mode = _mode;
}

int64_t CAnimation::GetCurrentFrame()
{
	return currentFrame;
}

void CAnimation::SetCurrentFrame(int64_t fr)
{
	currentFrame = fr;
	lastFrameTime = 0;
}

void CAnimation::GetSize(int64_t& width, int64_t& height)
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
