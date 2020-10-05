#include "TileSet.h"

CTileSet::CTileSet(LPDIRECT3DTEXTURE9 tex, map<int, Box<int>> map, int size)
{
	texture = tex;
	tileMap = map;
	tileSize = size;
}

void CTileSet::Draw(vector<vector<int>> matrix)
{
	for (int iY = 0; iY < matrix.size(); iY++)
	{
		for (int iX = 0; iX < matrix[0].size(); iX++)
		{
			int key = matrix[iY][iX];
			if (tileMap.count(key) == 0) continue;
			Box<int> tile = tileMap[key];

			CGraphic::Instance->Draw(
				texture,
				iX * tileSize, iY * tileSize,
				tile.left, tile.top, tile.right, tile.bottom, 0, 0, 1, false
			);
		}
	}
}
