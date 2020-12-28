#pragma once

#include "../Constraints.h"
#include "TileSet.h"
#include "../GraphicAndSound/Graphic.h"

class CTileMap
{
private:
	static CTileMap* __instance;
	LPTileSet curTileSet;
	vector<vector<int>> curMatrix;

public:
	static CTileMap* GetInstance();

	void Render();

	void SetTileSet(LPTileSet tileSet);
	void SetMatrix(vector<vector<int>> matrix);
};

