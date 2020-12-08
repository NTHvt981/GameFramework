#pragma once

#include <vector>
#include "../Constraints.h"

using namespace std;

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
	vector<CPatternUnit> units;
	int index;
	bool isFinish;

	Vector currentPosition;
	DWORD currentTime;

public:
	int GetIndex();
	bool GetIsFinish();

public:
	void Add(CPatternUnit unit);
	void Start();
	Vector Calculate(DWORD dt);
	void Update(DWORD dt);
};

