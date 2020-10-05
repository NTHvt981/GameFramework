#pragma once

#include <map>
#include <vector>
#include "../Constraints.h"
#include "../Vector/Box.h"
#include "../Graphic/Graphic.h"

using namespace std;

class CTileSet
{
private:
	LPDIRECT3DTEXTURE9 texture;
	map<int, Box<int>> tileMap;
	int tileSize;

public:
	CTileSet(LPDIRECT3DTEXTURE9 tex, map<int, Box<int>> map, int size);
	void Draw(vector<vector<int>> matrix);
};

