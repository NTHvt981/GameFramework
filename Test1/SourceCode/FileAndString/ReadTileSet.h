#pragma once

#include "../Vector/Box.h" 
#include "StringHelper.h"
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

/// <summary>
/// read info from a file
/// </summary>
/// <param name="tile_count">total number of tiles</param>
/// <param name="tile_width"></param>
/// <param name="tile_height"></param>
/// <param name="tile_count_width">columns of tiles</param>
/// <param name="tile_count_height">rows of tiles</param>
/// <param name="solid_tiles">list of id of wall tiles</param>
/// <param name="matrix">matrix of id of entire map</param>
/// <param name="tileDir">directory of tileset image file</param>
/// <param name="fileDir">input param, file to read</param>
void GetInfo(
	int &tile_count,
	int& tile_width, int& tile_height,
	int& tile_count_width, int& tile_count_height,
	vector<int> &solid_tiles,
	vector<vector<int>>& matrix,
	string& tileDir, string fileDir);

/// <summary>
/// get a map of tile
/// </summary>
/// <param name="tile_size_x"></param>
/// <param name="tile_size_y"></param>
/// <param name="tileset_size"></param>
/// <param name="result">a map with key is id, and box is ltrb of the image</param>
void GetMap(
	int tile_size_x, int tile_size_y,
	int tileset_size, map<int, Box<int>>& result
);

/// <summary>
/// scan matrix tileset, return a list of wall position and size (ltrb)
/// </summary>
/// <param name="pos_list"></param>
/// <param name="matrix"></param>
/// <param name="solid_tiles"></param>
/// <param name="tile_size"></param>
void SetWallPosition(
	vector<Box<float>> &pos_list, 
	vector<vector<int>> matrix,
	vector<int> solid_tiles,
	int tile_size);

Box<float> MakeBox(int iL, int iT, int iR, int iB, float tile_size);

vector<string> GetData(string fileDir);

