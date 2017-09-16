#include "gtest/gtest.h"

#include "test_utils.h"
#include "commander/view_state.h"
#include "commander/impl/ls_command.h"
#include "commander/impl/dir_command.h"


class Mock_view_state : public View_state
{
public:
    Mock_view_state() {}
    virtual std::vector<std::string> get_directory_listing(const std::string &dir) const
    {
        return { "get_directory_listing for " + dir };
    }
};



TEST(test_ls_command, execute)
{
    Mock_view_state state;
    LS_Command cmd(state);
    std::vector<std::string> args;

    args = {};
    EXPECT_EQ("get_directory_listing for .\n", cmd.execute(args));

    args = {"foo"};
    EXPECT_EQ("get_directory_listing for foo\n", cmd.execute(args));

    args = {"foo", "bar"};
    EXPECT_THROW_WITH_MESSAGE(cmd.execute(args), "ls requires 0 or 1 argument. 2 provided.");
}

// dir is alias for ls
TEST(test_dir_command, execute)
{
    Mock_view_state state;
    DIR_Command cmd(state);
    std::vector<std::string> args;

    args = {};
    EXPECT_EQ("get_directory_listing for .\n", cmd.execute(args));

    args = {"foo"};
    EXPECT_EQ("get_directory_listing for foo\n", cmd.execute(args));

    args = {"foo", "bar"};
    EXPECT_THROW_WITH_MESSAGE(cmd.execute(args), "dir requires 0 or 1 argument. 2 provided.");
}
