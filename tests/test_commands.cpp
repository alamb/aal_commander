#include "gtest/gtest.h"
#include "commands.h"
#include "command.h"
#include "parsed_line.h"
#include "view_state.h"

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