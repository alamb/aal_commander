#include "hints.h"
#include "parsed_line.h"

Hints::Hints()
{
}

// create the expected hints from a set of possibilities
Hints::Hints(Parsed_line &line, const std::vector<std::string> &completions)
{
    if (completions.empty())
    {
        hint_text_ = " (INVALID " + line.dump() + ")";
        color_ = COLOR_RED;
        bold_ = true;       
    }
    else if (completions.size() == 1)
    {
        hint_text_ = line.remove_command(completions[0]);
        color_ = COLOR_GREEN;
    }
    else
    {
        std::stringstream ss;
        
        // todo: cap length of suggestions/ prune common stems, etc
        for (const std::string &s : completions) 
        { 
            if (!ss.str().empty()) { ss << ", "; }
            ss << s;
        }
        hint_text_ = " [Available: " + ss.str() + "]";
        color_ = COLOR_MAGENTA;
    }
}
