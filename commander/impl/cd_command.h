#pragma once

#include "../command.h"

class CD_Command : public Command
{
public:
    CD_Command(View_state &state);
    std::vector<std::string> possible_completions(const std::vector<std::string> &args_so_far);
    std::string execute(const std::vector<std::string> &args) override;
};
