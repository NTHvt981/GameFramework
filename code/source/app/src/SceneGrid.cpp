#include "SceneGrid.h"

CSceneGrid::CSceneGrid(CScene* scene)
{
	this->scene = scene;
}

void CSceneGrid::RemoveEntity(int64_t id)
{
	entitiesId.remove(id);

	LPEntity e = scene->GetEntity(id);
	int64_t coId = e->GetCollisionBox()->GetId();

	colBoxesId.remove(coId);
}

void CSceneGrid::AddEntity(int64_t id)
{
	entitiesId.push_back(id);
	LPEntity e = scene->GetEntity(id);

	colBoxesId.push_back(e->GetCollisionBox()->GetId());

	count++;
}

std::list<int64_t> CSceneGrid::GetColBoxes() const
{
	return colBoxesId;
}

void CSceneGrid::SetLTRB(float l, float t, float r, float b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}

void CSceneGrid::Update(DWORD dt, int64_t& _count)
{
	//safe approach, ensure that if grid contain no entity -> exit func
	if (entitiesId.size() == 0) return;

	//do not remove entity while in the update loop, 
	//store remove ones in removeList
	//std::list<int64_t> removeList = std::list<int64_t>();

	std::list<int64_t>::iterator it = entitiesId.begin();

	for (const int64_t id: entitiesId)
	{
		//get the entity base on its id
		LPEntity e = scene->GetEntity(id);
		if (e == NULL) continue;
		//update the entity
		e->Update(dt);

		//this is for debug
		_count++;

		//check if entity is in grid boundary
		float x = e->GetCenter().x;
		float y = e->GetCenter().y;

		if (!((x >= left && x < right) && (y >= top && y < bottom)))
		{
			//add entity to remove std::list
			removeList.push_back(id);
		}
	}

	//remove all entities in remove std::list
	while (!removeList.empty())
	{
		LPEntity e = scene->GetEntity(removeList.front());
		//set the grid that entity is in
		//game->SetEntity(e);

		LPSceneRequest request = new CSceneRequest(SCENE_REQUEST_TYPES::SetEntity);
		request->entity = e;
		CSceneRequest::AddRequest(request);

		//this->RemoveEntity(e->GetId());
		removeList.pop_front();
	}
}

void CSceneGrid::Render()
{
	//safe approach, ensure that if grid contain no entity -> exit func
	if (entitiesId.size() == 0) return;

	std::list<int64_t>::iterator it;
	//loop through std::list, render the entity
	for (it = entitiesId.begin(); it != entitiesId.end(); ++it)
	{
		scene->GetEntity(
			*it
		)->Render();
	}
}

std::vector<std::vector<CSceneGrid*>> DivideSceneGrids(
	int64_t width, int64_t height, int64_t grid_width, int64_t grid_height, CScene* scene)
{
	std::vector<std::vector<CSceneGrid*>> grids;

	//cot
	int64_t cols = ceil(width / grid_width);
	//hang
	int64_t rows = ceil(height / grid_height);

	grids = std::vector<std::vector<CSceneGrid*>>(rows);

	for (int64_t i = 0; i < rows; i++)
	{
		grids[i] = std::vector<CSceneGrid*>(cols);

		for (int64_t j = 0; j < cols; j++)
		{
			grids[i][j] = new CSceneGrid(scene);

			grids[i][j]->SetLTRB(
				j * grid_width,
				i * grid_height,
				(j + 1) * grid_width,
				(i + 1) * grid_height
			);
		}
	}

	return grids;
}
