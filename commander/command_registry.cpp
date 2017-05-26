#include "command_registry.h"
#include "impl/cd_command.h"
#include "impl/pwd_command.h"
#include "impl/exit_command.h"

//static
std::vector<std::unique_ptr<Command>> Command_registry::get_commands(View_state &state)
{
    std::vector<std::unique_ptr<Command>> commands;
    commands.emplace_back(std::make_unique<CD_Command>(state));
    commands.emplace_back(std::make_unique<PWD_Command>(state));
    commands.emplace_back(std::make_unique<EXIT_Command>(state));
    return commands;
}
