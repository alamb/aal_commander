#include "ls_command.h"
#include "../view_state.h"

#include <sstream>


LS_Command::LS_Command(View_state &state) :
    Command("ls", state)
{}

LS_Command::LS_Command(const std::string &alias, View_state &state):
    Command(alias, state)
{
}


std::string LS_Command::execute(const std::vector<std::string> &args)
{
    std::string dir_arg;

    auto num_args = args.size();
    if (num_args == 0)
    {
        dir_arg = ".";
    }
    else if (num_args == 1)
    {
        dir_arg = args[0];
    }
    else
    {
        throw std::runtime_error(command_id() + " requires 0 or 1 argument. " +
                                 std::to_string(num_args) + " provided.");
    }

    std::stringstream ss;
    for (const auto &s : state_.get_directory_listing(dir_arg))
    {
        ss << s << std::endl;
    }
    return ss.str();
}
