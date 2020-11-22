#include "ReadTileSet.h"

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
        matrix.insert(matrix.end(), vector<int>());

        vector<string> segments = SplitString(line, " ");
        for (int j = 0; j < segments.size(); j++)
        {
            matrix[i-14.0].push_back(atoi(segments[j].c_str()));
        }
    }
}

void GetInfo(int& tile_count,
    int& tile_width, int& tile_height,
    int& tile_count_width, int& tile_count_height,
    vector<int>& solid_tiles,
    vector<int>& anti_player_tiles,
    vector<vector<int>>& matrix,
    string& tileDir, string fileDir)
{
    matrix.clear();
    solid_tiles.clear();
    anti_player_tiles.clear();

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
        solid_tiles.push_back(atoi(segments[i].c_str()));
    }

    segments = SplitString(lines[14], " ");
    for (int i = 0; i < segments.size(); i++)
    {
        anti_player_tiles.push_back(atoi(segments[i].c_str()));
    }

    for (int i = 16; i < lines.size(); i++)
    {
        string line = lines[i];
        //matrix.insert(0, vector<int>());
        matrix.insert(matrix.end(), vector<int>());

        vector<string> segments = SplitString(line, " ");
        for (int j = 0; j < segments.size(); j++)
        {
            matrix[i - 16].push_back(atoi(segments[j].c_str()));
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

    //reduce number of walls a little bit
    for (int iY = 0; iY < matrix.size(); iY += 2)
    {
        for (int iX = 0; iX < matrix[iY].size(); iX += 2)
        {
            vector<int>::iterator begin = solid_tiles.begin();
            vector<int>::iterator end = solid_tiles.end();

            //int iL, iT, iR, iB;
            //iL = iX;
            //iT = iY;
            //iR = iX + 1;
            //iB = iY + 1;

            // matrix[y][x]
            if (count(begin, end, matrix[iY][iX]) > 0 && count(begin, end, matrix[iY][iX+1]) > 0)
            {
                if (count(begin, end, matrix[iY+1][iX]) > 0 && count(begin, end, matrix[iY+1][iX+1]) > 0)
                    pos_list.push_back(MakeBox(iX, iY, iX+1, iY+1, tile_size));
                else
                {
                pos_list.push_back(MakeBox(iX, iY, iX+1, iY, tile_size));
                    
                if (count(begin, end, matrix[iY + 1][iX]) > 0)
                    pos_list.push_back(MakeBox(iX, iY + 1, iX, iY + 1, tile_size));
                if (count(begin, end, matrix[iY + 1][iX + 1]) > 0)
                    pos_list.push_back(MakeBox(iX + 1, iY + 1, iX + 1, iY + 1, tile_size));
                }
            }

            else if (count(begin, end, matrix[iY + 1][iX]) > 0 && 
                count(begin, end, matrix[iY + 1][iX + 1]) > 0)
            {
                pos_list.push_back(MakeBox(iX, iY + 1, iX + 1, iY + 1, tile_size));

                if (count(begin, end, matrix[iY][iX]) > 0)
                    pos_list.push_back(MakeBox(iX, iY, iX, iY, tile_size));
                if (count(begin, end, matrix[iY][iX+1]) > 0)
                    pos_list.push_back(MakeBox(iX+1, iY, iX+1, iY, tile_size));
            }

            else
            {
                if (count(begin, end, matrix[iY][iX + 1]) > 0 && count(begin, end, matrix[iY + 1][iX + 1]) > 0) 
                {
                    pos_list.push_back(MakeBox(iX + 1, iY, iX + 1, iY + 1, tile_size));

                    if (count(begin, end, matrix[iY][iX]) > 0)
                        pos_list.push_back(MakeBox(iX, iY, iX, iY, tile_size));
                    if (count(begin, end, matrix[iY + 1][iX]) > 0)
                        pos_list.push_back(MakeBox(iX, iY + 1, iX, iY + 1, tile_size));
                }
                else
                {
                    if (count(begin, end, matrix[iY][iX + 1]) > 0)
                        pos_list.push_back(MakeBox(iX + 1, iY, iX + 1, iY, tile_size));
                    if (count(begin, end, matrix[iY + 1][iX + 1]) > 0)
                        pos_list.push_back(MakeBox(iX + 1, iY + 1, iX + 1, iY + 1, tile_size));
                }

                if (count(begin, end, matrix[iY][iX]) > 0 && count(begin, end, matrix[iY + 1][iX]) > 0)
                    pos_list.push_back(MakeBox(iX, iY, iX, iY + 1, tile_size));
                else
                {
                    if (count(begin, end, matrix[iY][iX]) > 0)
                        pos_list.push_back(MakeBox(iX, iY, iX, iY, tile_size));
                    if (count(begin, end, matrix[iY + 1][iX]) > 0)
                        pos_list.push_back(MakeBox(iX, iY + 1, iX, iY + 1, tile_size));
                }
            }
                

            //continue == skip
            //if (iL == -1 || iT == -1) continue;

            //Box<float> box;

            //box.left = iL * tile_size;
            //box.right = (iR + 1) * tile_size;

            //box.top = (iT)*tile_size;
            //box.bottom = (iB + 1) * tile_size;

            //pos_list.push_back(box);
        }
    }
}

Box<float> MakeBox(int iL, int iT, int iR, int iB, float tile_size)
{
    Box<float> box;

    box.left = iL * tile_size;
    box.right = (iR + 1) * tile_size;

    box.top = (iT)*tile_size;
    box.bottom = (iB + 1) * tile_size;

    return box;
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