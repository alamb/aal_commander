#include "parsed_line.h"
#include <sstream>

Parsed_line::Parsed_line(const std::string &s)
{
    std::istringstream iss(s);
    iss >> command_;

    while (iss)
    {
        args_.emplace_back();
        iss >> args_.back();
        if (args_.back().empty())
        {
            args_.pop_back();
        }
    }
}

std::string Parsed_line::dump() const
{
    std::stringstream ss;
    ss << "[" << command_ << "] (";
    for (size_t i = 0; i < args_.size(); ++i)
    {
        if (i > 0)
        {
            ss << ", ";
        }
        ss << args_[i];
    }
    ss << ")";
    return ss.str();
}

std::string Parsed_line::remove_command(const std::string &s)
{
    size_t idx = 0;
    while (idx < s.size() && idx < command_.size() && s[idx] == command_[idx])
    {
        idx++;
    }
    // consume any additional spaces
    while (idx < s.size() && s[idx] == ' ') { idx++; }

    return s.substr(idx);
}
