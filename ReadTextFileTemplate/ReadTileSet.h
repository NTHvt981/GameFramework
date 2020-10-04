#pragma once

#include "Box.h" 
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

vector<string> GetData(string fileDir);

