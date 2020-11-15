#include "Timer.h"

list<CTimer> CTimer::timers = list<CTimer>();

CTimer::CTimer(DWORD waitTime) {
	this->waitTime = waitTime;
}

void CTimer::Start()
{
    this->Reset();
    this->Attach();
}

void CTimer::Reset()
{
    currentTime = 0;
}

bool CTimer::IsFinish()
{
    return (currentTime == waitTime);
}

DWORD CTimer::GetCurrentTime()
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

bool CTimer::operator==(CTimer timer)
{
    return false;
}

void CTimer::Attach()
{
    timers.push_back(*this);
}

void CTimer::Detach()
{

}

void CTimer::Update(DWORD dt) {
	currentTime = min(currentTime + dt, waitTime);
    if (currentTime == waitTime) Detach();
}

void CTimer::UpdateAll(DWORD dt)
{
    //Create an iterator of std::list
    std::list<CTimer>::iterator it;
    for (it = timers.begin(); it != timers.end(); it++)
    {
        it->Update(dt);
    }
}
