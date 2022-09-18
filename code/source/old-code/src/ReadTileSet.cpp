#include "ReadTileSet.h"

void GetInfo(int64_t& tile_count, 
    int64_t& tile_width, int64_t& tile_height, 
    int64_t& tile_count_width, int64_t& tile_count_height,
    std::vector<int64_t>& solid_tiles,
    std::vector<std::vector<int64_t>>& matrix, 
    std::string& tileDir, std::string fileDir)
{
    matrix.clear();
    solid_tiles.clear();

    std::vector<std::string> lines = GetData(fileDir);

    tileDir = lines[0];

    tile_count = atoi(lines[2].c_str());
    tile_width = atoi(lines[4].c_str());
    tile_height = atoi(lines[6].c_str());
    tile_count_width = atoi(lines[8].c_str());
    tile_count_height = atoi(lines[10].c_str());

    std::vector<std::string> segments = SplitString(lines[12], " ");
    for (int64_t i = 0; i < segments.size(); i++)
    {
        solid_tiles.push_back( atoi(segments[i].c_str()) );
    }

    for (int64_t i = 14; i < lines.size(); i++)
    {
        std::string line = lines[i];
        //matrix.insert(0, std::vector<int64_t>());
        matrix.insert(matrix.end(), std::vector<int64_t>());

        std::vector<std::string> segments = SplitString(line, " ");
        for (int64_t j = 0; j < segments.size(); j++)
        {
            matrix[i-14.0].push_back(atoi(segments[j].c_str()));
        }
    }
}

void GetInfo(int64_t& tile_count,
    int64_t& tile_width, int64_t& tile_height,
    int64_t& tile_count_width, int64_t& tile_count_height,
    std::vector<int64_t>& solid_tiles,
    std::vector<int64_t>& anti_player_tiles,
    std::vector<std::vector<int64_t>>& matrix,
    std::string& tileDir, std::string fileDir)
{
    matrix.clear();
    solid_tiles.clear();
    anti_player_tiles.clear();

    std::vector<std::string> lines = GetData(fileDir);

    tileDir = lines[0];

    tile_count = atoi(lines[2].c_str());
    tile_width = atoi(lines[4].c_str());
    tile_height = atoi(lines[6].c_str());
    tile_count_width = atoi(lines[8].c_str());
    tile_count_height = atoi(lines[10].c_str());

    std::vector<std::string> segments = SplitString(lines[12], " ");
    for (int64_t i = 0; i < segments.size(); i++)
    {
        solid_tiles.push_back(atoi(segments[i].c_str()));
    }

    segments = SplitString(lines[14], " ");
    for (int64_t i = 0; i < segments.size(); i++)
    {
        anti_player_tiles.push_back(atoi(segments[i].c_str()));
    }

    for (int64_t i = 16; i < lines.size(); i++)
    {
        std::string line = lines[i];
        //matrix.insert(0, std::vector<int64_t>());
        matrix.insert(matrix.end(), std::vector<int64_t>());

        std::vector<std::string> segments = SplitString(line, " ");
        for (int64_t j = 0; j < segments.size(); j++)
        {
            matrix[i - 16].push_back(atoi(segments[j].c_str()));
        }
    }
}

void GetMap(
    int64_t tile_size_x, int64_t tile_size_y, 
    int64_t tileset_size, std::map<int64_t, Box<int64_t>>& result)
{
    result.clear();

    for (int64_t i = 0; i < tileset_size; i++)
    {
        Box<int64_t> box;

        box.left = i * tile_size_x;
        box.top = 0;
        box.right = (i + 1) * tile_size_x;
        box.bottom = tile_size_y;

        result[i] = box;
    }
}

void SetWallPosition(
    std::vector<Box<float>>& pos_list,
    std::vector<std::vector<int64_t>> matrix,
    std::vector<int64_t> solid_tiles,
    int64_t tile_size)
{

    //reduce number of walls a little bit
    for (int64_t iY = 0; iY < matrix.size(); iY += 2)
    {
        for (int64_t iX = 0; iX < matrix[iY].size(); iX += 2)
        {
            std::vector<int64_t>::iterator begin = solid_tiles.begin();
            std::vector<int64_t>::iterator end = solid_tiles.end();

            //int64_t iL, iT, iR, iB;
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

Box<float> MakeBox(int64_t iL, int64_t iT, int64_t iR, int64_t iB, float tile_size)
{
    Box<float> box;

    box.left = iL * tile_size;
    box.right = (iR + 1) * tile_size;

    box.top = (iT)*tile_size;
    box.bottom = (iB + 1) * tile_size;

    return box;
}

std::vector<std::string> GetData(std::string fileDir)
{
    std::vector<std::string> lines;
    std::fstream newFile;
    newFile.open(fileDir);

    if (newFile.is_open())
    {
        std::string line;
        while (std::getline(newFile, line)) {
            lines.push_back(line);
        }

        newFile.close();
    }

    return lines;
}