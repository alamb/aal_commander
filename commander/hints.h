#pragma once

#include <sstream>
#include <string>
#include <vector>

class Parsed_line;

class Hints
{
public:
    Hints();

    // create the expected hints from a set of possibilities
    Hints(Parsed_line &line, const std::vector<std::string> &possibilities);    

    static const int COLOR_MAGENTA = 35;
    static const int COLOR_RED     = 31;
    static const int COLOR_GREEN   = 32;

    // access
    int  color()                   const { return color_; }
    bool bold()                    const { return bold_;  }
    const std::string &hint_text() const { return hint_text_; }

private:
    int color_ = COLOR_MAGENTA;
    std::string hint_text_;
    bool bold_ = false;
};
