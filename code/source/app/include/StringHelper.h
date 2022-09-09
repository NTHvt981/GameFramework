#pragma once

#include <string>
#include <list>
#include <vector>

std::vector<std::string> SplitString(const std::string str, const std::string delim);
template <typename T>
std::string GetItemInList(std::list<std::string> _list, int64_t _i);
std::string Trim(const std::string& str);
bool Contain(std::string _string, std::string _subString);
void Remove(std::string& _string, std::string _subString);