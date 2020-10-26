#include "Grid.h"

void CGrid::RemoveEntity(int id)
{
	//entitiesId.remove(id);
	list<int>::iterator it;
	for (it = entitiesId.begin(); it != entitiesId.end(); ++it)
	{
		if (*it == id)
		{
			entitiesId.erase(it);
			return;
		}
	}
}

void CGrid::AddEntity(int id)
{
	entitiesId.push_back(id);
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
	if (entitiesId.size() == 0) return;

	list<int> removeList = list<int>();

	CGame* game = CGame::GetInstance();
	list<int>::iterator it = entitiesId.begin();
	while (it != entitiesId.end())
	{
		LPEntity e = game->GetEntity(*it);
		e->Update(dt);

		//this is for debug
		count++;

		//check if entity is in grid boundary
		float x = e->GetPosition().x;
		float y = e->GetPosition().y;
		if (!((x >= left && x < right) && (y >= top && y < bottom)))
		{
			removeList.push_back(*it);
		}
		++it;
	}

	while (!removeList.empty())
	{
		LPEntity e = game->GetEntity(removeList.front());
		game->SetEntity(e);

		entitiesId.remove(removeList.front());
		removeList.pop_front();
	}
}

void CGrid::Render()
{
	if (entitiesId.size() == 0) return;

	CGame* game = CGame::GetInstance();
	list<int>::iterator it;
	for (it = entitiesId.begin(); it != entitiesId.end(); ++it)
	{
		game->GetEntity(
			*it
		)->Render();
	}
}

vector<vector<CGrid>> DivideGrids(int width, int height, int grid_width, int grid_height)
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
