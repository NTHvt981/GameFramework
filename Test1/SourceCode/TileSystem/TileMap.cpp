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

void CTileMap::SetMatrix(vector<vector<int>> matrix)
{
	curMatrix = matrix;
}
