#include "pwd_command.h"
#include "../view_state.h"

PWD_Command::PWD_Command(View_state &state) : 
    Command("pwd", state) 
{}

std::string PWD_Command::execute(const std::vector<std::string> &args)
{
    return "Current working directory: " + state_.cwd();
}
