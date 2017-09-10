#include "cd_command.h"
#include "commander/view_state.h"
#include <stdexcept>

CD_Command::CD_Command(View_state &state) :
    Command("cd", state)
{}

std::vector<std::string> CD_Command::possible_completions(const std::vector<std::string> &args_so_far)
{
    std::vector<std::string> paths;

    const std::string &partial_path = args_so_far.empty() ? "" : args_so_far[0];

    for (const std::string &current_path : state_.get_directories())
    {
        if (partial_path.empty() || (current_path.find(partial_path) == 0))
        {
            paths.push_back(command_id_ + " " + current_path);
        }
    }
    return paths;
}

std::string CD_Command::execute(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        throw std::runtime_error("No argument provided");
    }
    else if (args.size() == 1)
    {
        state_.cd(args[0]);
        return "Changed directory to " + args[0];
    }
    else
    {
       throw std::runtime_error("Too many arguments provided");
    }
}
