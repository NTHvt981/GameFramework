#pragma once

#include "../Constraints.h"
#include <list>
#include <vector>
#include "../SceneSystem/Scene.h"
#include "../SceneSystem/SceneRequest.h"

using namespace std;

class CSceneGrid
{
private:
	CScene* scene;

	// list of entities id (not entity obj) within each grid
	list<int> entitiesId = list<int>();
	// list of collision box id (not co box obj) within each grid
	list<int> colBoxesId = list<int>();

	//these vars use to check if entity belong in this grid or not
	float left;
	float top;
	float right;
	float bottom;

	int count = 0;

	list<int> removeList = list<int>();

public:
	CSceneGrid(CScene *scene);

	void RemoveEntity(int id);
	void AddEntity(int id);

	list<int> GetColBoxes();
	list<int> GetColBoxes(int ex);
	void SetLTRB(float l, float t, float r, float b);

	//this get called in game update func
	void Update(DWORD dt, int& count);
	//this get called in game render func
	void Render();
};

vector<vector<CSceneGrid*>> DivideSceneGrids(
	int width, int height, int grid_width, int grid_height, CScene *scene);