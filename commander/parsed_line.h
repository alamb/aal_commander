#pragma once

#include <vector>
#include <string>

/**
 * Parses a string into a "command" and some number of arguments.
 */
class Parsed_line
{
public:
    Parsed_line();
    Parsed_line(const std::string &s);
    std::string dump() const;

    // remove as much of s is left after removing command_
    std::string remove_command_and_args(const std::string &s) const;

    const std::string              &command() const { return command_; }
    const std::vector<std::string> &args()    const { return args_;    }

private:
    std::string              command_;
    std::vector<std::string> args_;
};
