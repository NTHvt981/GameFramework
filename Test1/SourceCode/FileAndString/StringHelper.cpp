#include "StringHelper.h"

bool Contain(string _string, string _subString)
{
    int pos = _string.find(_subString);
    return pos != string::npos;
}

void Remove(string& _string, string _subString)
{
    int index = _string.find(_subString);
    while (index != string::npos)
    {
        _string.erase(index, _subString.length());
        index = _string.find(_subString);
    }
}

vector<string> SplitString(const string str, const string delim)
{
    vector<string> tokens;
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

string Trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

//wstring s2ws(const string& s)
//{
//    int len;
//    int slength = (int)s.length() + 1;
//    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
//    wchar_t* buf = new wchar_t[len];
//    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
//    std::wstring r(buf);
//    delete[] buf;
//    return r;
//}