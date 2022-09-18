#include "TileMap.h"

CTileMap* CTileMap::__instance = NULL;

CTileMap* CTileMap::GetInstance()
{
	if (__instance == NULL) __instance = new CTileMap();
	return __instance;
}

void CTileMap::Render()
{
	curTileSet->Draw(curMatrix);
}

void CTileMap::SetTileSet(LPTileSet tileSet)
{
	curTileSet = tileSet;
}

void CTileMap::SetMatrix(std::vector<std::vector<int64_t>> matrix)
{
	curMatrix = matrix;
}
