#include "gtest/gtest.h"
#include "commands.h"
#include "command.h"
#include "parsed_line.h"
#include "view_state.h"

#include "test_utils.h"

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

class test_commands : public ::testing::Test 
{
public:
protected:
    View_state state_;
};


TEST_F(test_commands, get_command)
{
    Commands commands;
    commands.add_command(std::make_unique<Dummy_command>("cd", state_));

    Parsed_line p("cd");
    EXPECT_EQ("cd", commands.get_command(p).command_id());

    p = Parsed_line("ccd");
    EXPECT_THROW_WITH_MESSAGE(commands.get_command(p), "Unknown command ccd");

}