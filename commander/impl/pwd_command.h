#pragma once
#include "../command.h"

class PWD_Command : public Command
{
public:
    PWD_Command(View_state &state);
    std::string execute(const std::vector<std::string> &args) override;
};
