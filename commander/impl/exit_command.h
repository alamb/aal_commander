#pragma once
#include "../command.h"

class EXIT_Command : public Command
{
public:
    EXIT_Command(View_state &state);
    std::string execute(const std::vector<std::string> &args) override;
};
