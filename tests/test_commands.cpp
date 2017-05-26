#include "gtest/gtest.h"
#include "commander/commands.h"
#include "commander/command.h"
#include "commander/parsed_line.h"
#include "commander/view_state.h"

#include "test_utils.h"
#include "dummy_command.h"

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

TEST_F(test_commands, get_possible_completions)
{
    Commands commands;
    commands.add_command(std::make_unique<Dummy_command>("cd", state_));
    commands.add_command(std::make_unique<Dummy_command>("pwd", state_));

    Parsed_line p;
    p = Parsed_line("");
    EXPECT_EQ(strvec({"pwd", "cd"}), commands.get_possible_completions(p));

    p = Parsed_line("p");
    EXPECT_EQ(strvec({"pwd"}), commands.get_possible_completions(p));

    p = Parsed_line("pw");
    EXPECT_EQ(strvec({"pwd"}), commands.get_possible_completions(p));

    p = Parsed_line("pwd");
    EXPECT_EQ(strvec({"pwd"}), commands.get_possible_completions(p));
}