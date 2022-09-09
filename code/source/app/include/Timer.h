#pragma once

#include "Constraints.h"
#include <list>



class CTimer
{
private:
	//be cautious
	//current must be add up, not minus down
	//current time minus dt in update lead to bug
	DWORD currentTime;
	DWORD waitTime;
	//bool finish = false;
	bool pause = false;
public:
	CTimer(DWORD waitTime);
	void Start();
	void Update(DWORD dt);
	void Pause();
	void UnPause();
	bool IsFinish();
	bool JustFinish();

	DWORD GetTimeLeft();
	DWORD GetWaitTime();
	void SetWaitTime(DWORD t);
};

