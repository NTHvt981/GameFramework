#include "Pattern.h"

CPatternUnit::CPatternUnit(Vector pos, DWORD time)
{
	Position = pos;
	Time = time;
}

int CPattern::GetIndex()
{
	return index;
}

bool CPattern::GetIsFinish()
{
	return isFinish;
}

void CPattern::Add(CPatternUnit unit)
{
	units.push_back(unit);
}

void CPattern::Start()
{
	index = 0;
	isFinish = false;
	
	currentTime = 0;

	currentPosition.x = startPosition.x;
	currentPosition.y = startPosition.y;
}

Vector CPattern::Calculate(DWORD dt)
{
	if (index >= units.size())
		return Vector(0, 0);

	DWORD time = units[index].Time;
	Vector goal = units[index].Position;

	float _x = (goal.x - currentPosition.x) * (dt / time);
	float _y = (goal.y - currentPosition.y) * (dt / time);

	return Vector(_x, _y);
}

void CPattern::Update(DWORD dt)
{
	currentTime += dt;
	DWORD time = units[index].Time;
	Vector goal = units[index].Position;

	if (currentTime >= time)
	{
		currentTime = 0;
		currentPosition.x = goal.x;
		currentPosition.y = goal.y;

		index++;
		if (index >= units.size())
			isFinish = true;
	}
}
