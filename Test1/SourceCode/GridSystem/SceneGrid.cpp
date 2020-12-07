#include "SceneGrid.h"

CSceneGrid::CSceneGrid(CScene* scene)
{
	this->scene = scene;
}

void CSceneGrid::RemoveEntity(int id)
{
	entitiesId.remove(id);

	LPEntity e = scene->GetEntity(id);
	int coId = e->GetCollisionBox()->GetId();

	colBoxesId.remove(coId);
}

void CSceneGrid::AddEntity(int id)
{
	entitiesId.push_back(id);
	LPEntity e = scene->GetEntity(id);

	colBoxesId.push_back(e->GetCollisionBox()->GetId());

	count++;
}

list<int> CSceneGrid::GetColBoxes()
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

void CSceneGrid::Update(DWORD dt, int& _count)
{
	//safe approach, ensure that if grid contain no entity -> exit func
	if (entitiesId.size() == 0) return;

	//do not remove entity while in the update loop, 
	//store remove ones in removeList
	//list<int> removeList = list<int>();

	list<int>::iterator it = entitiesId.begin();

	for each (int id in entitiesId)
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
			//add entity to remove list
			removeList.push_back(id);
		}
	}

	//remove all entities in remove list
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

	list<int>::iterator it;
	//loop through list, render the entity
	for (it = entitiesId.begin(); it != entitiesId.end(); ++it)
	{
		scene->GetEntity(
			*it
		)->Render();
	}
}

vector<vector<CSceneGrid*>> DivideSceneGrids(
	int width, int height, int grid_width, int grid_height, CScene* scene)
{
	vector<vector<CSceneGrid*>> grids;

	//cot
	int cols = ceil(width / grid_width);
	//hang
	int rows = ceil(height / grid_height);

	grids = vector<vector<CSceneGrid*>>(rows);

	for (int i = 0; i < rows; i++)
	{
		grids[i] = vector<CSceneGrid*>(cols);

		for (int j = 0; j < cols; j++)
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
