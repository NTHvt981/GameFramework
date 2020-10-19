#pragma once

#include "../Constraints.h"
#include <list>

using namespace std;

class CTimer
{
private:
	DWORD currentTime;
	DWORD waitTime;
	bool finish;

	static list<CTimer> timers;

public:
	CTimer(DWORD waitTime);
	void Start();
	void Reset();
	bool IsFinish();

	DWORD GetCurrentTime();
	DWORD GetWaitTime();
	void SetWaitTime(DWORD t);
	bool operator ==(CTimer timer);
private:
	void Update(DWORD dt);
	void Attach();
	void Detach();
public:
	static void UpdateAll(DWORD dt);
};

