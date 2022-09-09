#pragma once

#include <map>
#include <vector>
#include "Constraints.h"
#include "Core/Box.h"
#include "Graphic.h"



class CTileSet
{
private:
	LPDIRECT3DTEXTURE9 texture;
	std::map<int64_t, Box<int64_t>> tileMap;
	int64_t tileSize;

public:
	CTileSet(LPDIRECT3DTEXTURE9 tex, std::map<int64_t, Box<int64_t>> i_map, int64_t size);

	//unlike before, now tile set only draw tiles within the camera
	void Draw(std::vector<std::vector<int64_t>> matrix);
};

