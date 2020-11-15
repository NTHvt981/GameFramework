#pragma once

#include "../Vector/Box.h" 
#include "StringHelper.h"
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

void GetInfo(int& tile_size_x, int& tile_size_y,
	int& tileset_size_x, int& tileset_size_y,
	int& padding, int& margin, vector<vector<int>>& matrix,
	string &tileDir, string fileDir);

void GetMap(
	int tile_size_x, int tile_size_y,
	int tileset_size_x, int tileset_size_y,
	int padding, int margin, map<int, Box<int>> &result);


void GetInfo(
	int &tile_count,
	int& tile_width, int& tile_height,
	int& tile_count_width, int& tile_count_height,
	vector<int> &solid_tiles,
	vector<vector<int>>& matrix,
	string& tileDir, string fileDir);

void GetMap(
	int tile_size_x, int tile_size_y,
	int tileset_size, map<int, Box<int>>& result
);

void SetWallPosition(
	vector<Box<float>> &pos_list, 
	vector<vector<int>> matrix,
	vector<int> solid_tiles,
	int tile_size);

vector<string> GetData(string fileDir);

