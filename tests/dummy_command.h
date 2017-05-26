#include "command.h"

class View_state;

class Dummy_command : public Command
{
    public: 
        Dummy_command(const std::string &id, View_state &state) :
            Command(id, state) {}

    std::string execute(const std::vector<std::string> &args) override
    {
        return "Ran command " + command_id();
    }

};
