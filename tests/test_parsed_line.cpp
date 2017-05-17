#include "gtest/gtest.h"
#include "parsed_line.h"

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

TEST(test_parse_line, remove_command)
{
    Parsed_line p("c");
    EXPECT_EQ("d", p.remove_command("cd"));

    p = Parsed_line ("cd");
    EXPECT_EQ("", p.remove_command("cd"));
    EXPECT_EQ("", p.remove_command("cd "));
    EXPECT_EQ("f", p.remove_command("cd f"));
    EXPECT_EQ("foo", p.remove_command("cd foo"));
    EXPECT_EQ("foo ", p.remove_command("cd foo "));
}