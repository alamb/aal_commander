#include "command.h"
#include <stdexcept>
#include "view_state.h"





std::vector<std::string> Command::possible_completions(const std::vector<std::string> &args_so_far) 
{
    // default completion is for no arg commands which is the command itself.
    return std::vector<std::string>({ command_id() });
}

