#include "exit_command.h"
#include "../view_state.h"

EXIT_Command::EXIT_Command(View_state &state) : 
   Command("exit", state) 
{}

std::string EXIT_Command::execute(const std::vector<std::string> &args)
{
    state_.set_exit_requested();
    return "Exiting...";
}
