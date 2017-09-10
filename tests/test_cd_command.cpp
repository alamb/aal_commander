#include "gtest/gtest.h"

#include "test_utils.h"
#include "commander/view_state.h"
#include "commander/impl/cd_command.h"


// TODO: factor this into its own test file
TEST(test_cd_command, cd_command_execute)
{
    // test plumbing connection
    View_state state;
    CD_Command cmd(state);
    std::vector<std::string> args;

    // maybe should go to home directory?
    args = {};
    EXPECT_THROW_WITH_MESSAGE(cmd.execute(args), "No argument provided");

    args = {"foo"};
    std::string foo_path = state.pwd() + "/foo";
    EXPECT_THROW_WITH_MESSAGE(cmd.execute(args), "No such directory: " + foo_path);

    args = {"foo", "bar"};
    EXPECT_THROW_WITH_MESSAGE(cmd.execute(args), "Too many arguments provided");
}
