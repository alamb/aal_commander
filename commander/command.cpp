#include "command.h"
#include <stdexcept>
#include "view_state.h"



class CD_Command : public Command
{
  public:
    CD_Command(View_state &state) : Command("cd", state) {}

    std::vector<std::string> possible_completions(const std::vector<std::string> &args_so_far)
    {
        std::vector<std::string> paths;

        const std::string &partial_path = args_so_far.empty() ? "" : args_so_far[0];

        for (const std::string &current_path : state_.get_directories())
        {
            if (partial_path.empty() || (current_path.find(partial_path) == 0))
            {
                paths.push_back(command_id_ + " " + current_path);
            }
        }
        return paths;
    }


    std::string execute(const std::vector<std::string> &args) override
    {
        throw std::runtime_error("Not yet implemented");
    }
};

class PWD_Command : public Command
{
  public:
    PWD_Command(View_state &state) : Command("pwd", state) {}

    std::string execute(const std::vector<std::string> &args) override
    {
        return "Current working directory: " + state_.cwd();
    }
};

// command that starts with the same letter, just to test auto complete
class PPWD_Command : public Command
{
  public:
    PPWD_Command(View_state &state) : Command("ppwd", state) {}

    std::string execute(const std::vector<std::string> &args) override
    {
        return "Current working directory: " + state_.cwd();
    }
};

std::vector<std::string> Command::possible_completions(const std::vector<std::string> &args_so_far) 
{
    return std::vector<std::string>();
}


//static
std::vector<std::unique_ptr<Command>> Command::get_commands(View_state &state)
{
    std::vector<std::unique_ptr<Command>> commands;
    commands.emplace_back(std::make_unique<CD_Command>(state));
    commands.emplace_back(std::make_unique<PWD_Command>(state));
    commands.emplace_back(std::make_unique<PPWD_Command>(state));
   return commands;
}