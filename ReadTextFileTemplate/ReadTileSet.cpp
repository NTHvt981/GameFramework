#include "ReadTileSet.h"

void GetInfo(
    int& tile_size_x, int& tile_size_y,
    int& tileset_size_x, int& tileset_size_y,
    int& padding, int& margin, vector<vector<int>> &matrix,
    string& tileDir, string fileDir)
{
    vector<string> lines = GetData(fileDir);
    int map_detail_index = 0;

    for (int i = 0; i < lines.size(); i++)
    {
        string line = lines[i];
        
        if (Contain(line, "TILEMAP"))
        {
            map_detail_index = i+1;
            break;
        }
        if (Contain(line, "//")) continue;
        if (Trim(line) == "") continue;

        vector<string> segments = SplitString(line, " ");
        if (segments[0] == "source")
        {
            tileDir = segments[1].c_str();
        }
        else if (segments[0] == "tile_padding")
        {
            padding = atoi(segments[1].c_str());
        }
        else if (segments[0] == "tile_margin")
        {
            margin = atoi(segments[1].c_str());
        }
        else if (segments[0] == "tile_size")
        {
            tile_size_x = atoi(segments[1].c_str());
            tile_size_y = atoi(segments[2].c_str());
        }
        else if (segments[0] == "tileset_size")
        {
            tileset_size_x = atoi(segments[1].c_str());
            tileset_size_y = atoi(segments[2].c_str());
        }
    }

    for (int i = map_detail_index; i < lines.size(); i++)
    {
        string line = lines[i];
        matrix.push_back(vector<int>());

        vector<string> segments = SplitString(line, ",");
        for (int i = 0; i < segments.size(); i++)
        {
            matrix.back().push_back(atoi(segments[i].c_str()));
        }
    }
}

void GetMap(
    int tile_size_x, int tile_size_y,
    int tileset_size_x, int tileset_size_y,
    int padding, int margin, map<int, Box<int>>& result)
{
    result.clear();

    for (int iY = 0; iY < tileset_size_y; iY++)
    {
        for (int iX = 0; iX < tileset_size_x; iX++)
        {
            int tile_index = tileset_size_y * iY + iX + 1;
            Box<int> box;

            box.left = iX * tile_size_x + iX * padding;
            box.top = iY * tile_size_y + iY * padding;
            box.right = box.left + tile_size_x - 1;
            box.bottom = box.top + tile_size_x - 1;

            result[tile_index] = box;
        }
    }
}

vector<string> GetData(string fileDir)
{
    vector<string> lines;
    fstream newFile;
    newFile.open(fileDir);

    if (newFile.is_open())
    {
        string line;
        while (getline(newFile, line)) {
            lines.push_back(line);
        }

        newFile.close();
    }

    return lines;
}