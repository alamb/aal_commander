#include "gtest/gtest.h"
#include "commander/parsed_line.h"

TEST(test_parsed_line, construct)
{
    Parsed_line p("");
    EXPECT_EQ("", p.command());
    EXPECT_EQ(0, p.args().size());

    p = Parsed_line("cd");
    EXPECT_EQ("cd", p.command());
    EXPECT_EQ(0, p.args().size());

    p = Parsed_line("cd ");
    EXPECT_EQ("cd", p.command());
    EXPECT_EQ(0, p.args().size());

    p = Parsed_line("cd foo");
    EXPECT_EQ("cd", p.command());
    EXPECT_EQ(std::vector<std::string>({"foo"}), p.args());

    // extra spaces
    p = Parsed_line("cd  foo");
    EXPECT_EQ("cd", p.command());
    EXPECT_EQ(std::vector<std::string>({"foo"}), p.args());

    // 3 extra spaces
    p = Parsed_line("cd   foo");
    EXPECT_EQ("cd", p.command());
    EXPECT_EQ(std::vector<std::string>({"foo"}), p.args());

    // multiple args
    p = Parsed_line("cd foo bar");
    EXPECT_EQ("cd", p.command());
    EXPECT_EQ(std::vector<std::string>({"foo", "bar"}), p.args());

    // multiple args with spaces
    p = Parsed_line("cd  foo   bar");
    EXPECT_EQ("cd", p.command());
    EXPECT_EQ(std::vector<std::string>({"foo", "bar"}), p.args());
}

TEST(test_parse_line, remove_command_and_args)
{
    Parsed_line p("c");
    EXPECT_EQ("d",    p.remove_command_and_args("cd"));

    p = Parsed_line("cd");
    EXPECT_EQ("",     p.remove_command_and_args("cd"));
    EXPECT_EQ("",     p.remove_command_and_args("cd "));
    EXPECT_EQ("f",    p.remove_command_and_args("cd f"));
    EXPECT_EQ("foo",  p.remove_command_and_args("cd foo"));
    EXPECT_EQ("foo ", p.remove_command_and_args("cd foo "));
}
TEST(test_parse_line, remove_command_and_args_with_arg)
{
    // parsed line with an argument
    Parsed_line p("cd a");
    EXPECT_EQ("",     p.remove_command_and_args("cd"));
    EXPECT_EQ("",     p.remove_command_and_args("cd "));
    EXPECT_EQ("",     p.remove_command_and_args("cd a"));
    EXPECT_EQ("nd",   p.remove_command_and_args("cd and"));
    EXPECT_EQ("f",    p.remove_command_and_args("cd f"));
    EXPECT_EQ("foo",  p.remove_command_and_args("cd foo"));
    EXPECT_EQ("foo ", p.remove_command_and_args("cd foo "));
}

TEST(test_parse_line, remove_command_and_args_with_2_args)
{
    // parsed line with two arguments
    Parsed_line p("cd andrew la");
    EXPECT_EQ("",     p.remove_command_and_args("cd"));
    EXPECT_EQ("",     p.remove_command_and_args("cd "));
    EXPECT_EQ("",     p.remove_command_and_args("cd a"));
    EXPECT_EQ("",     p.remove_command_and_args("cd and"));
    EXPECT_EQ("x",    p.remove_command_and_args("cd andx"));
    EXPECT_EQ("",     p.remove_command_and_args("cd andre"));
    EXPECT_EQ("",     p.remove_command_and_args("cd andrew "));
    EXPECT_EQ("xx",   p.remove_command_and_args("cd andrew xx"));
    EXPECT_EQ("",     p.remove_command_and_args("cd andrew la"));
    EXPECT_EQ("qx",   p.remove_command_and_args("cd andrew laqx"));
    EXPECT_EQ("qx s", p.remove_command_and_args("cd andrew laqx s"));
    EXPECT_EQ("mb",   p.remove_command_and_args("cd andrew lamb"));
    EXPECT_EQ("mb qx",p.remove_command_and_args("cd andrew lamb qx"));
    EXPECT_EQ("f",    p.remove_command_and_args("cd f"));
    EXPECT_EQ("foo",  p.remove_command_and_args("cd foo"));
    EXPECT_EQ("foo ", p.remove_command_and_args("cd foo "));
}