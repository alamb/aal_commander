#include "commands.h"
#include "parsed_line.h"
#include "command.h"

#include <algorithm>

static void append(std::vector<std::string> &dst, const std::vector<std::string> &src)
{
    for (const auto &s : src)
    {
        dst.push_back(s);
    }
}

Commands::Commands(std::vector<std::unique_ptr<Command>> &&commands) : 
    commands_(std::move(commands))
{
}

void Commands::add_command(std::unique_ptr<Command> &&command)
{
    commands_.emplace_back(std::move(command));
}


std::string Commands::run_command(const Parsed_line &line)
{
    return get_command(line.command()).execute(line.args());
}

Command& Commands::get_command(const Parsed_line &line)
{
    std::string command = line.command();

    for (const auto &cmd : commands_)
    {
        if (command == cmd->command_id())
        {
            return *cmd;
        }
    }
    throw std::runtime_error("Unknown command " + command);
}

std::vector<std::string> Commands::get_possible_completions(const Parsed_line &line)
{
    std::vector<std::string> completions;

    // first see if any of the commands totally match
    for (const auto &cmd : commands_)
    {
        if (line.command() == cmd->command_id())
        {
            append(completions, cmd->possible_completions(line.args()));
        }
        // otherwise see if the currently specified command is a prefix
        else if (line.command().empty() || cmd->command_id().find(line.command()) == 0)
        {
            completions.push_back(cmd->command_id());
        }
    }
    return completions;
}

// return the common prefix size between two strings
static size_t prefix_size(const std::string &s1, const std::string &s2)
{
    size_t sz = 0;
    while (sz < s1.size() && sz < s2.size() && s1[sz] == s2[sz]) { sz++; }
    return sz;
}

//static 
std::vector<std::string> Commands::collapse_completions(const std::vector<std::string> &completions)
{
    // the idea is to find all elements with a common prefix and collapse them into that common prefix. 
    std::vector<std::string> sorted = completions;

    // The basic idea: sort the strings and then collapse the elements together. Perhaps it is inefficient but that is ok.
    std::sort(sorted.begin(), sorted.end()); // lexically sort

    std::vector<std::string> results;
    if (sorted.empty()) { return results; }

    std::string curprefix = sorted[0];
    for (size_t i=0; i<sorted.size(); ++i)
    {
        size_t common_size = prefix_size(curprefix, sorted[i]);
        // if no common prefix, just add to the results
        if (common_size == 0) 
        { 
            results.push_back(curprefix); 
            curprefix = sorted[i];
        }
        // if there is a common prefix, adjust curprefix as necessary and keep going
        else
        {
            curprefix = curprefix.substr(0, common_size);
        }
    }
    results.push_back(curprefix);
    return results;
}
