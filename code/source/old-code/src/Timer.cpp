#include "Timer.h"

CTimer::CTimer(DWORD waitTime) {
	this->waitTime = waitTime;
    currentTime = 0;
    pause = true;
}

void CTimer::Start()
{
    pause = false;
    currentTime = 0;
}

bool CTimer::IsFinish()
{
    return (currentTime == waitTime);
}

bool CTimer::JustFinish()
{
    if (IsFinish() && !pause)
    {
        pause = true;
        return true;
    }

    return false;
}

DWORD CTimer::GetTimeLeft()
{
    return currentTime;
}

DWORD CTimer::GetWaitTime()
{
    return waitTime;
}

void CTimer::SetWaitTime(DWORD t)
{
    this->waitTime = t;
}

void CTimer::Update(DWORD dt) {
    if (pause) return;

    currentTime = min(currentTime + dt, waitTime); 

    //DebugOut(L"[INFO] time left %d\n", currentTime);
}

void CTimer::Pause()
{
    pause = true;
}

void CTimer::UnPause()
{
    pause = false;
}

