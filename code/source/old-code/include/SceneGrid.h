#pragma once

#include "Constraints.h"
#include <list>
#include <vector>
#include "Scene.h"
#include "SceneRequest.h"



class CSceneGrid
{
private:
	CScene* scene;

	// std::list of entities id (not entity obj) within each grid
	std::list<int64_t> entitiesId = std::list<int64_t>();
	// std::list of collision box id (not co box obj) within each grid
	std::list<int64_t> colBoxesId = std::list<int64_t>();

	//these vars use to check if entity belong in this grid or not
	float left;
	float top;
	float right;
	float bottom;

	int64_t count = 0;

	std::list<int64_t> removeList = std::list<int64_t>();

public:
	CSceneGrid(CScene *scene);

	void RemoveEntity(int64_t id);
	void AddEntity(int64_t id);

	std::list<int64_t> GetColBoxes() const;
	std::list<int64_t> GetColBoxes(int64_t ex) const;
	void SetLTRB(float l, float t, float r, float b);

	//this get called in game update func
	void Update(DWORD dt, int64_t& count);
	//this get called in game render func
	void Render();
};

std::vector<std::vector<CSceneGrid*>> DivideSceneGrids(
	int64_t width, int64_t height, int64_t grid_width, int64_t grid_height, CScene *scene);