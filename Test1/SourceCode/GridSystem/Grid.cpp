#include "Grid.h"

void CGrid::RemoveEntity(int id)
{
	entitiesId.remove(id);

	LPEntity e = CGame::GetInstance()->GetEntity(id);
	int coId = e->GetCollisionBox()->GetId();
	colBoxesId.remove(coId);
}

void CGrid::AddEntity(int id)
{
	entitiesId.push_back(id);
	LPEntity e = CGame::GetInstance()->GetEntity(id);
	colBoxesId.push_back(e->GetCollisionBox()->GetId());
}

list<int> CGrid::GetColBoxes()
{
	return colBoxesId;
}

void CGrid::SetLTRB(float l, float t, float r, float b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}

void CGrid::Update(DWORD dt, int &count)
{
	//safe approach, ensure that if grid contain no entity -> exit func
	if (entitiesId.size() == 0) return;

	//do not remove entity while in the update loop, store remove ones in this
	list<int> removeList = list<int>();

	CGame* game = CGame::GetInstance();
	list<int>::iterator it = entitiesId.begin();
	while (it != entitiesId.end())
	{
		//get the entity base on its id
		LPEntity e = game->GetEntity(*it);
		//update the entity
		e->Update(dt);

		//this is for debug
		count++;

		//check if entity is in grid boundary
		float x = e->GetPosition().x;
		float y = e->GetPosition().y;
		if (!((x >= left && x < right) && (y >= top && y < bottom)))
		{
			//add entity to remove list
			removeList.push_back(*it);
		}
		++it;
	}

	//remove all entities in remove list
	while (!removeList.empty())
	{
		LPEntity e = game->GetEntity(removeList.front());
		//set the grid that entity is in
		game->SetEntity(e);

		this->RemoveEntity(e->GetId());
		removeList.pop_front();
	}
}

void CGrid::Render()
{
	//safe approach, ensure that if grid contain no entity -> exit func
	if (entitiesId.size() == 0) return;

	CGame* game = CGame::GetInstance();
	list<int>::iterator it;
	//loop through list, render the entity
	for (it = entitiesId.begin(); it != entitiesId.end(); ++it)
	{
		game->GetEntity(
			*it
		)->Render();
	}
}

vector<vector<CGrid>> DivideGrids(
	int width, int height, int grid_width, int grid_height)
{
	vector<vector<CGrid>> grids;
	
	//cot
	int cols = ceil(width / grid_width);
	//hang
	int rows = ceil(height / grid_height);

	grids = vector<vector<CGrid>>(rows);

	for (int i = 0; i < rows; i++)
	{
		grids[i] = vector<CGrid>(cols);

		for (int j = 0; j < cols; j++)
		{
			grids[i][j].SetLTRB(
				j * grid_width,
				i * grid_height,
				(j + 1) * grid_width,
				(i + 1) * grid_height
			);
		}
	}

	return grids;
}
