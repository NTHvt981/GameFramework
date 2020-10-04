#pragma once
#include <map>
#include <string>

#include "Box.h"

using namespace std;

class CTileSet
{
private:
	int id;
	string name;
	map<int, Box<int>> tileMap;

};

