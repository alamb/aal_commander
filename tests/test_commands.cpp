#include "gtest/gtest.h"
#include "commander/commands.h"
#include "commander/command.h"
#include "commander/parsed_line.h"
#include "commander/view_state.h"

#include "commander/impl/cd_command.h"

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
    EXPECT_EQ(strvec({"cd", "pwd"}), commands.get_possible_completions(p));

    p = Parsed_line("p");
    EXPECT_EQ(strvec({"pwd"}), commands.get_possible_completions(p));

    p = Parsed_line("pw");
    EXPECT_EQ(strvec({"pwd"}), commands.get_possible_completions(p));

    p = Parsed_line("pwd");
    EXPECT_EQ(strvec({"pwd"}), commands.get_possible_completions(p));
}

TEST_F(test_commands, collapse_completions_no_common)
{
    EXPECT_EQ(strvec({}), 
              Commands::collapse_completions(strvec({})));
    EXPECT_EQ(strvec({"def"}), 
              Commands::collapse_completions(strvec({"def"})));
    EXPECT_EQ(strvec({"abc", "def"}), 
              Commands::collapse_completions(strvec({"def", "abc"})));
    EXPECT_EQ(strvec({"abc", "def"}), 
              Commands::collapse_completions(strvec({"abc", "def"})));
}

TEST_F(test_commands, collapse_completions_prefix)
{
    EXPECT_EQ(strvec({"abc", "def"}), 
              Commands::collapse_completions(strvec({"def", "abc", "abc"})));

    EXPECT_EQ(strvec({"abc", "def"}), 
              Commands::collapse_completions(strvec({"def", "abc", "abcd"})));

    EXPECT_EQ(strvec({"abc", "def"}), 
              Commands::collapse_completions(strvec({"abc", "def", "abcd"})));

    EXPECT_EQ(strvec({"abc", "def"}), 
              Commands::collapse_completions(strvec({"def", "abc", "abcd", "abc"})));

    EXPECT_EQ(strvec({"ab", "def"}), 
              Commands::collapse_completions(strvec({"def", "ab", "abcd", "abc"})));

    EXPECT_EQ(strvec({"abc", "def", "ef"}), 
              Commands::collapse_completions(strvec({"def", "abc", "abcd", "abc", "ef"})));

    EXPECT_EQ(strvec({"abc", "de"}), 
              Commands::collapse_completions(strvec({"def", "abc", "abcd", "abc", "de"})));

    EXPECT_EQ(strvec({"abc", "de", "gi"}), 
              Commands::collapse_completions(strvec({"def", "abc", "abcd", "abc", "de", "gi", "gig"})));

}

// TODO: factor this into its own test file
TEST_F(test_commands, cd_command_execute)
{
    // test plumbing connection
    CD_Command cmd(state_);
    std::vector<std::string> args;

    // maybe should go to home directory?   
    args = {};
    EXPECT_THROW_WITH_MESSAGE(cmd.execute(args), "No argument provided");

    args = {"foo"};
    std::string foo_path = state_.pwd() + "/foo";
    EXPECT_THROW_WITH_MESSAGE(cmd.execute(args), "No such directory: " + foo_path);

    args = {"foo", "bar"};
    EXPECT_THROW_WITH_MESSAGE(cmd.execute(args), "Too many arguments provided");
} 


