#include "ls_command.h"
#include "../view_state.h"

#include <sstream>


LS_Command::LS_Command(View_state &state) : 
    Command("ls", state) 
{}

std::string LS_Command::execute(const std::vector<std::string> &args)
{
    std::stringstream ss;
    for (const auto &s : state_.get_directory_listing())
    {
        ss << s << std::endl;
    }
    return ss.str();
}
