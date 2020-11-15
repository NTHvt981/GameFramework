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

	//get width and height of map (in tiles)
	int tile_count_width, tile_count_height;
	tile_count_width = matrix[0].size();
	tile_count_height = matrix.size();
	
	//Get the start and end of the tiles position base on camera l, t, r, b
	startX = max((l / tileSize), 0);
	endX = min(ceil(r / tileSize), tile_count_width - 1);

	startY = max((t / tileSize), 0);
	endY = min(ceil(b / tileSize), tile_count_height - 1);

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


	//DEBUG
	DebugOut(L"[INFO] Number of tiles total: %d\n", (matrix.size() * matrix[0].size()));
	DebugOut(L"[INFO] Number of tiles render: %d\n", (endY - startY)*(endX - startX));
}
