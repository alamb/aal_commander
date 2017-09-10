#include "gtest/gtest.h"
#include "test_utils.h"
#include "test_directory.h"

#include "commander/view_state.h"

#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

TEST(test_view_state, defaut_dir)
{
    Test_directory dir;
    View_state state(dir.base_directory());

    EXPECT_EQ(dir.base_directory(), state.pwd());
}

TEST(test_view_state, cwd)
{
    Test_directory dir;
    View_state state(dir.base_directory());

    EXPECT_THROW_WITH_MESSAGE(state.cd("foo"), "No such directory: " + dir.base_directory() + "/foo");
    dir.mkdir("foo");
    EXPECT_NO_THROW(state.cd("foo"));

    fs::path actual_dir = dir.base_path() / "foo";
    EXPECT_EQ(actual_dir.string(), state.pwd());
}

TEST(test_view_state, cwd_to_dot)
{
    Test_directory dir;
    View_state state(dir.base_directory());

    dir.mkdir("foo");
    dir.mkdir("foo/bar");

    fs::path foo_dir = dir.base_path() / "foo";
    fs::path bar_dir = foo_dir / "bar";

    state.cd("foo");
    EXPECT_EQ(foo_dir.string(), state.pwd());
    state.cd("bar");
    EXPECT_EQ(bar_dir.string(), state.pwd());
    state.cd(".");
    EXPECT_EQ(bar_dir.string(), state.pwd());
    state.cd("..");
    EXPECT_EQ(foo_dir.string(), state.pwd());
    state.cd("..");
    EXPECT_EQ(dir.base_path().string(), state.pwd());
}


TEST(test_view_state, cwd_to_file)
{
    Test_directory dir;
    View_state state(dir.base_directory());

    // test changing directory to a file
    dir.mkdir("foo");
    dir.write_file("foo/bar.txt", "the contents");
    EXPECT_TRUE(fs::exists(dir.base_directory() / fs::path("foo/bar.txt")));
    EXPECT_TRUE(fs::is_regular_file(dir.base_path() / fs::path("foo/bar.txt")));

    state.cd("foo");
    EXPECT_THROW_WITH_MESSAGE(state.cd("bar.txt"),
                              "Path not directory: " + dir.base_directory() + "/foo/bar.txt");
    EXPECT_THROW_WITH_MESSAGE(state.cd("foo/bar.txt"),
                              "No such directory: " + dir.base_directory() + "/foo/foo/bar.txt");
}
