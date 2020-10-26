#include "TileSet.h"

CTileSet::CTileSet(LPDIRECT3DTEXTURE9 tex, map<int, Box<int>> map, int size)
{
	texture = tex;
	tileMap = map;
	tileSize = size;
}

void CTileSet::Draw(vector<vector<int>> matrix)
{
	float l, t, r, b;
	CCamera::GetInstance()->GetLTRB(l, t, r, b);
	int startX, startY, endX, endY;

	startX = max((l / tileSize) - 1, 0);
	endX = ceil(r / tileSize);

	startY = max((t / tileSize) - 1, 0);
	endY = ceil(b / tileSize);

	for (int iY = startY; iY <= endY; iY++)
	{
		for (int iX = startX; iX <= endX; iX++)
		{
			int key = matrix[iY][iX];
			if (tileMap.count(key) == 0) continue;
			Box<int> tile = tileMap[key];

			CGraphic::Instance->Draw(
				texture,
				iX * tileSize, iY * tileSize,
				tile.left, tile.top, tile.right, tile.bottom
			);
		}
	}
}
