#include "hints.h"
#include "parsed_line.h"

#include <algorithm>

const int Hints::COLOR_MAGENTA = 35;
const int Hints::COLOR_RED     = 31;
const int Hints::COLOR_GREEN   = 32;


Hints::Hints()
{
}

// create the expected hints from a set of possibilities
Hints::Hints(const Parsed_line &line, const std::vector<std::string> &completions)
{
    if (completions.empty())
    {
        hint_text_ = " (INVALID " + line.dump() + ")";
        color_ = COLOR_RED;
        bold_ = true;       
    }
    else if (completions.size() == 1)
    {
        hint_text_ = line.remove_command_and_args(completions[0]);
        color_ = COLOR_GREEN;
    }
    else
    {
        // find longest common prefix between all completions
        std::string common_prefix = completions[0];
        for (const std::string &s : completions) 
        {
            size_t len = 0;
            while (len < s.size() &&  len < common_prefix.size() && 
                   common_prefix[len] == s[len]) 
            {
                len++;
            }
            common_prefix = common_prefix.substr(0,len);
        }

        // create a sorted list of remaining completions (sorted by shortest to longest)
        std::vector<std::string> remainders;
        for (const std::string &s : completions)
        {
            if (s.size() > common_prefix.size()) 
            {
                remainders.emplace_back(s.substr(common_prefix.size()));
            }
        }
        std::sort(remainders.begin(), 
                 remainders.end(), 
                 [](const auto &s1, const auto &s2) {
                     return s1.size() < s2.size(); 
                 });

        std::stringstream ss;
        ss << "{";
        bool first = true;
        for (const std::string &s : remainders) 
        { 
            if (!first) { ss << ","; }
            first = false;
            ss << s;
        }
        ss << "}";
        hint_text_ = line.remove_command_and_args(common_prefix) + ss.str();
        color_ = COLOR_MAGENTA;
    }
}
