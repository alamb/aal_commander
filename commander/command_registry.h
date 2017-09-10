#pragma once

#include <vector>
#include <memory>
#include "command.h"

class View_state;
class Command;

/**
 * Encapsulates all available commands in commander
 */
class Command_registry
{
public:
    // available commands
    static std::vector<std::unique_ptr<Command> > get_commands(View_state &state);
};
