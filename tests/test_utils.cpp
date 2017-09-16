#include "test_utils.h"
#include <sstream>


std::string to_string(const std::vector<std::string> &v)
{
    std::stringstream ss;
    ss << "(";
    bool first = true;
    for (const auto &s: v)
    {
        if (!first) ss << ", ";
        first = false;
        ss << s;
    }
    ss << ")";
    return ss.str();
}
