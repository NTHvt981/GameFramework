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
        //matrix.insert(0, vector<int>());
        matrix.insert(matrix.begin(), vector<int>());

        vector<string> segments = SplitString(line, ",");
        for (int j = 0; j < segments.size(); j++)
        {
            matrix.front().push_back(atoi(segments[j].c_str()));
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
            box.right = box.left + tile_size_x;
            box.bottom = box.top + tile_size_y;

            result[tile_index] = box;
        }
    }
}

void GetInfo(int& tile_count, 
    int& tile_width, int& tile_height, 
    int& tile_count_width, int& tile_count_height,
    vector<int>& solid_tiles,
    vector<vector<int>>& matrix, 
    string& tileDir, string fileDir)
{
    matrix.clear();
    solid_tiles.clear();

    vector<string> lines = GetData(fileDir);

    tileDir = lines[0];

    tile_count = atoi(lines[2].c_str());
    tile_width = atoi(lines[4].c_str());
    tile_height = atoi(lines[6].c_str());
    tile_count_width = atoi(lines[8].c_str());
    tile_count_height = atoi(lines[10].c_str());

    vector<string> segments = SplitString(lines[12], " ");
    for (int i = 0; i < segments.size(); i++)
    {
        solid_tiles.push_back( atoi(segments[i].c_str()) );
    }

    for (int i = 14; i < lines.size(); i++)
    {
        string line = lines[i];
        //matrix.insert(0, vector<int>());
        matrix.insert(matrix.begin(), vector<int>());

        vector<string> segments = SplitString(line, " ");
        for (int j = 0; j < segments.size(); j++)
        {
            matrix.front().push_back(atoi(segments[j].c_str()));
        }
    }
}

void GetMap(
    int tile_size_x, int tile_size_y, 
    int tileset_size, map<int, Box<int>>& result)
{
    result.clear();

    for (int i = 0; i < tileset_size; i++)
    {
        Box<int> box;

        box.left = i * tile_size_x;
        box.top = 0;
        box.right = (i + 1) * tile_size_x;
        box.bottom = tile_size_y;

        result[i] = box;
    }
}

void SetWallPosition(
    vector<Box<float>>& pos_list,
    vector<vector<int>> matrix,
    vector<int> solid_tiles,
    int tile_size)
{
    for (int iY = 0; iY < matrix.size(); iY++)
    {
        for (int iX = 0; iX < matrix[iY].size(); iX++)
        {
            if (count(solid_tiles.begin(), solid_tiles.end(), matrix[iY][iX]) > 0)
            {
                Box<float> box;

                box.left = iX * tile_size;
                box.right = (iX + 1) * tile_size;

                box.top = (iY - 1) * tile_size;
                box.bottom = (iY) * tile_size;

                pos_list.push_back(box);
            }
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