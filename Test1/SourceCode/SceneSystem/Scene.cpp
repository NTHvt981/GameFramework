#include "Scene.h"

LPEntity CScene::GetEntity(int id)
{
	return mapEntities[id];
}

void LoadFileParam(
	int &tile_count, int &tile_width, int &tile_height, 
	int &tile_count_width, int &tile_count_height,
	vector<int> &solid_tiles, vector<int> &anti_player_tiles,
	vector<vector<int>> &matrix,
	wstring &tileSetDir, string fileDir
)
{
	string tileDir;

	GetInfo(tile_count, tile_width, tile_height,
		tile_count_width, tile_count_height,
		solid_tiles, anti_player_tiles,
		matrix, tileDir, fileDir);

	map<int, Box<int>> tileMap;
	GetMap(tile_width, tile_height, tile_count, tileMap);

	tileSetDir = std::wstring(tileDir.begin(), tileDir.end());
}

void GetGridXandY(
	int& startX, int& startY, int& endX, int& endY,
	float left, float top, float right, float bottom,
	float gridWidth, float gridHeight,
	int grid_count_width,
	int grid_count_height)
{
	startX = max((left / gridWidth) - 1, 0);
	endX = min(right / gridWidth + 1, grid_count_width - 1);

	startY = max((top / gridHeight) - 1, 0);
	endY = min(bottom / gridHeight + 1, grid_count_height - 1);
}
