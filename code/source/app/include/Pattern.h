#pragma once

#include <vector>
#include "Constraints.h"



class CPatternUnit
{
public:
	Vector Position;
	DWORD Time;

	CPatternUnit(Vector pos, DWORD time=0);
};

class CPattern
{
	Vector startPosition;
	std::vector<CPatternUnit> units;
	int64_t index;
	bool isFinish;

	Vector currentPosition;
	DWORD currentTime;

public:
	int64_t GetIndex();
	bool GetIsFinish();

public:
	void Add(CPatternUnit unit);
	void Start();
	Vector Calculate(DWORD dt);
	void Update(DWORD dt);
};

