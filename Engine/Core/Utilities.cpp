#include "Utilities.h"

#include <algorithm>

namespace nh
{
    std::string nh::ToLower(const std::string& string)
    {
        std::string s = string;

        std::transform(string.begin(), string.end(), s.begin(), [](char c)
        {
            return std::tolower(c);
        });

        return s;
    }

    bool ICompare(const std::string& string1, const std::string& string2)
    {
        return std::equal(string1.begin(), string1.end(), string2.begin(), [](char c1, char c2)
        {
            return (std::tolower(c1) == std::tolower(c2));
        });
    }
}
