#include "TileSet.h"

CTileSet::CTileSet(LPDIRECT3DTEXTURE9 tex, std::map<int64_t, Box<int64_t>> i_map, int64_t size)
{
	texture = tex;
	tileMap = i_map;
	tileSize = size;
}

void CTileSet::Draw(std::vector<std::vector<int64_t>> matrix)
{
	float l, t, r, b;
	CCamera::GetInstance()->GetLTRB(l, t, r, b);
	int64_t startX, startY, endX, endY;

	//get width and height of std::map (in tiles)
	int64_t tile_count_width, tile_count_height;
	tile_count_width = matrix[0].size();
	tile_count_height = matrix.size();
	
	//Get the start and end of the tiles position base on camera l, t, r, b
	startX = max((l / tileSize), 0);
	endX = min(ceil(r / tileSize), tile_count_width - 1.0);

	startY = max((t / tileSize), 0);
	endY = min(ceil(b / tileSize), tile_count_height - 1.0);

	for (int64_t iY = startY; iY <= endY; iY++)
	{
		for (int64_t iX = startX; iX <= endX; iX++)
		{
			int64_t key = matrix[iY][iX];
			if (tileMap.count(key) == 0) continue;
			Box<int64_t> tile = tileMap[key];

			CGraphic::Instance->DrawWithTransformation(
				texture,
				iX * tileSize, iY * tileSize,
				tile.left, tile.top, tile.right, tile.bottom
			);
		}
	}


	//DEBUG
/*	DebugOut(L"[INFO] Number of tiles total: %d\n", (matrix.size() * matrix[0].size()));
	DebugOut(L"[INFO] Number of tiles render: %d\n", (endY - startY)*(endX - startX));
	*/
}
