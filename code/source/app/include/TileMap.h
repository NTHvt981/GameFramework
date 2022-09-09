#pragma once

#include "Constraints.h"
#include "TileSet.h"
#include "Graphic.h"

class CTileMap
{
private:
	static CTileMap* __instance;
	LPTileSet curTileSet;
	std::vector<std::vector<int64_t>> curMatrix;

public:
	static CTileMap* GetInstance();

	void Render();

	void SetTileSet(LPTileSet tileSet);
	void SetMatrix(std::vector<std::vector<int64_t>> matrix);
};

