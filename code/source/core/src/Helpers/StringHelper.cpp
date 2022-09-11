#include "Core/Helpers/StringHelper.h"

namespace data_types::string
{

std::vector<String> Split(const String i_totalStr, const String i_delimiter)
{
    size_t start;
    size_t end = 0;
    std::vector<String> result;
    while ((start = i_totalStr.FindFirstNotOf(i_delimiter, end)) != std::string::npos)
    {
        end = i_totalStr.Find(i_delimiter, start);
        const String& stdResult = i_totalStr.SubString(start, end - start);
        result.push_back(stdResult);
    }

    return result;
}

} // namespace data_types::string
