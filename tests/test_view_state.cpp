#include "gtest/gtest.h"
#include "test_utils.h"
#include "test_directory.h"

#include "commander/view_state.h"

#include "boost/filesystem.hpp"


namespace fs = boost::filesystem;

class Test_view_state : public View_state 
{
public:
    Test_view_state(const Test_directory &td) : 
        View_state(td.base_directory()) 
    {}
};


TEST(test_view_state, pwd_cwd)
{
    Test_directory dir;
    Test_view_state state(dir);

    EXPECT_EQ(dir.base_directory(), state.pwd());
    EXPECT_THROW_WITH_MESSAGE(state.cd("foo"), "No such directory: " + dir.base_directory() + "/foo");

    dir.mkdir("foo");
    EXPECT_NO_THROW(state.cd("foo"));
    
    fs::path actual_dir = fs::path(dir.base_directory()) / fs::path("foo");
    EXPECT_EQ(actual_dir.string(), state.pwd());

    // test changing directory fo a file
    dir.write_file("foo/bar.txt", "the contents");
    EXPECT_TRUE(fs::exists(dir.base_directory() / fs::path("foo/bar.txt")));
    EXPECT_TRUE(fs::is_regular_file(dir.base_directory() / fs::path("foo/bar.txt")));

    EXPECT_THROW_WITH_MESSAGE(state.cd("bar.txt"), "Path not directory: " + dir.base_directory() + "/foo/bar.txt");
    EXPECT_THROW_WITH_MESSAGE(state.cd("foo/bar.txt"), "No such directory: " + dir.base_directory() + "/foo/foo/bar.txt");
}

