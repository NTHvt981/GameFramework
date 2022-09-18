#include "Scene.h"

LPEntity CScene::GetEntity(int64_t id)
{
	return mapEntities[id];
}

void LoadFileParam(
	int64_t &tile_count, int64_t &tile_width, int64_t &tile_height, 
	int64_t &tile_count_width, int64_t &tile_count_height,
	std::vector<int64_t> &solid_tiles, std::vector<int64_t> &anti_player_tiles,
	std::vector<std::vector<int64_t>> &matrix,
	std::wstring &tileSetDir, std::string fileDir
)
{
	std::string tileDir;

	GetInfo(tile_count, tile_width, tile_height,
		tile_count_width, tile_count_height,
		solid_tiles, anti_player_tiles,
		matrix, tileDir, fileDir);

	std::map<int64_t, Box<int64_t>> tileMap;
	GetMap(tile_width, tile_height, tile_count, tileMap);

	tileSetDir = std::wstring(tileDir.begin(), tileDir.end());
}

void GetGridXandY(
	int64_t& startX, int64_t& startY, int64_t& endX, int64_t& endY,
	float left, float top, float right, float bottom,
	float gridWidth, float gridHeight,
	int64_t grid_count_width,
	int64_t grid_count_height)
{
	startX = max((left / gridWidth) - 1, 0);
	endX = min(right / gridWidth + 1, grid_count_width - 1);

	startY = max((top / gridHeight) - 1, 0);
	endY = min(bottom / gridHeight + 1, grid_count_height - 1);
}
