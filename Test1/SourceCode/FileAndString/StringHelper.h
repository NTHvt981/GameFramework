#pragma once

#include <string>
#include <list>
#include <vector>

using namespace std;

vector<string> SplitString(const string str, const string delim);
template <typename T>
string GetItemInList(list<string> _list, int _i);
string Trim(const string& str);
bool Contain(string _string, string _subString);
void Remove(string& _string, string _subString);