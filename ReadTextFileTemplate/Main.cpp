// ReadTextFileTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Box.h"
#include "StringHelper.h"
#include "ReadTileSet.h"

using namespace std;

int main()
{
    int tile_size_x, tile_size_y, tileset_size_x, tileset_size_y;
    int padding, margin;
    vector<vector<int>> matrix;
    string tileDir, fileDir;

    fileDir = "Resource/Textfile/temp_tilemap_info.txt";
    
    GetInfo(
        tile_size_x, tile_size_y,
        tileset_size_x, tileset_size_y,
        padding, margin, matrix,
        tileDir, fileDir);

    map<int, Box<int>> result;
    GetMap(tile_size_x, tile_size_x,
        tileset_size_x, tileset_size_y,
        padding, margin,
        result);
    std::cout << "Hello World!\n";
}
