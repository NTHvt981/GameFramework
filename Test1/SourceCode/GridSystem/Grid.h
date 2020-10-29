#pragma once
#include "../Constraints.h"
#include <list>
#include <vector>
#include "../Game/Game.h"

using namespace std;

class CGrid
{
private:
	list<int> entitiesId = list<int>();
	list<int> colBoxesId = list<int>();
	float left;
	float top;
	float right;
	float bottom;
	
public:
	void RemoveEntity(int id);
	void AddEntity(int id);

	list<int> GetColBoxes();
	void SetLTRB(float l, float t, float r, float b);

	void Update(DWORD dt, int &count);
	void Render();
};

vector<vector<CGrid>> DivideGrids(
	int width, int height, int grid_width, int grid_height);
