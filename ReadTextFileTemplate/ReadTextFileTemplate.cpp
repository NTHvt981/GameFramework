// ReadTextFileTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "Box.h"

using namespace std;


list<string> SplitString(const string str, const string delim);
string GetItemInList(list<string> _list, int _i);
string trim(const string& str);

int main()
{
    list<Box<int>> boxes;
    fstream newFile;
    newFile.open("Resource/Textfile/temp_sprite_info.txt");

    if (newFile.is_open())
    {
        string line;
        while (getline(newFile, line)) {
            //check whether string is a comment (contain //)
            if (line.find_first_of("//") != string::npos)
                continue;

            if (trim(line) == "")
                continue;

            list<string> segments = SplitString(line, "\t");

            Box<int> box;

            auto lFront = segments.begin();

            box.left = atoi( segments.front().c_str() );
            box.top = atoi(GetItemInList(segments, 1).c_str());
            box.right = atoi(GetItemInList(segments, 2).c_str());
            box.bottom = atoi(GetItemInList(segments, 3).c_str());

            boxes.push_back(box);
        }

        newFile.close();
    }

    std::cout << "Hello World!\n";
}

list<string> SplitString(const string str, const string delim)
{
    list<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

string GetItemInList(list<string> _list, int _i) {
    list<string>::iterator it = _list.begin();
    for (int i = 0; i < _i; i++) {
        ++it;
    }
    return *it;
}

string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}