#include "StringHelper.h"

bool Contain(std::string _string, std::string _subString)
{
    int64_t pos = _string.find(_subString);
    return pos != std::string::npos;
}

void Remove(std::string& _string, std::string _subString)
{
    int64_t index = _string.find(_subString);
    while (index != std::string::npos)
    {
        _string.erase(index, _subString.length());
        index = _string.find(_subString);
    }
}

std::vector<std::string> SplitString(const std::string str, const std::string delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

std::string GetItemInList(std::list<std::string> _list, int64_t _i) {
    std::list<std::string>::iterator it = _list.begin();
    for (int64_t i = 0; i < _i; i++) {
        ++it;
    }
    return *it;
}

std::string Trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

//std::wstring s2ws(const std::string& s)
//{
//    int64_t len;
//    int64_t slength = (int64_t)s.length() + 1;
//    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
//    wchar_t* buf = new wchar_t[len];
//    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
//    std::std::wstring r(buf);
//    delete[] buf;
//    return r;
//}