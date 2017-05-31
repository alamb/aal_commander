#pragma once
#include "../command.h"

class LS_Command : public Command
{
public:
    LS_Command(View_state &state);
    std::string execute(const std::vector<std::string> &args) override;
protected:
    LS_Command(const std::string &alias, View_state &state);
};
