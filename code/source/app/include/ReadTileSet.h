#pragma once

#include "Core/Box.h" 
#include "StringHelper.h"
#include <fstream>
#include <map>
#include <vector>
#include <string>



/// <summary>
/// read info from a file
/// </summary>
/// <param name="tile_count">total number of tiles</param>
/// <param name="tile_width"></param>
/// <param name="tile_height"></param>
/// <param name="tile_count_width">columns of tiles</param>
/// <param name="tile_count_height">rows of tiles</param>
/// <param name="solid_tiles">std::list of id of wall tiles</param>
/// <param name="matrix">matrix of id of entire std::map</param>
/// <param name="tileDir">directory of tileset image file</param>
/// <param name="fileDir">input param, file to read</param>
void GetInfo(
	int64_t &tile_count,
	int64_t& tile_width, int64_t& tile_height,
	int64_t& tile_count_width, int64_t& tile_count_height,
	std::vector<int64_t> &solid_tiles,
	std::vector<std::vector<int64_t>>& matrix,
	std::string& tileDir, std::string fileDir);

void GetInfo(int64_t& tile_count,
	int64_t& tile_width, int64_t& tile_height,
	int64_t& tile_count_width, int64_t& tile_count_height,
	std::vector<int64_t>& solid_tiles,
	std::vector<int64_t>& anti_player_tiles,
	std::vector<std::vector<int64_t>>& matrix,
	std::string& tileDir, std::string fileDir);

/// <summary>
/// get a std::map of tile
/// </summary>
/// <param name="tile_size_x"></param>
/// <param name="tile_size_y"></param>
/// <param name="tileset_size"></param>
/// <param name="result">a std::map with key is id, and box is ltrb of the image</param>
void GetMap(
	int64_t tile_size_x, int64_t tile_size_y,
	int64_t tileset_size, std::map<int64_t, Box<int64_t>>& result
);

/// <summary>
/// scan matrix tileset, return a std::list of wall position and size (ltrb)
/// </summary>
/// <param name="pos_list"></param>
/// <param name="matrix"></param>
/// <param name="solid_tiles"></param>
/// <param name="tile_size"></param>
void SetWallPosition(
	std::vector<Box<float>> &pos_list, 
	std::vector<std::vector<int64_t>> matrix,
	std::vector<int64_t> solid_tiles,
	int64_t tile_size);

Box<float> MakeBox(int64_t iL, int64_t iT, int64_t iR, int64_t iB, float tile_size);

std::vector<std::string> GetData(std::string fileDir);

