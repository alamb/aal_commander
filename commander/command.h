#pragma once
#include <string>
#include <memory>
#include <vector>

class View_state;

// Commands have the structure "<cmd_id>" and potentially an argument
class Command
{
public:
    virtual ~Command() {}

    const std::string &command_id()             const { return command_id_; }

    // return a list of possible completions given the command that was specified so far
    virtual std::vector<std::string> possible_completions(const std::vector<std::string> &args_so_far);

    // do whatever it is that the command is supposed to do. return status message. 
    // throws exception on error
    virtual std::string execute(const std::vector<std::string> &args) = 0;

protected:
    Command(const std::string &id, View_state &state) : 
        command_id_(id), state_(state) {}

    const std::string command_id_;
    View_state &state_;
};
