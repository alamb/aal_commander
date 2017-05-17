#include "commands.h"
#include "parsed_line.h"
#include "command.h"

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