#include "gtest/gtest.h"
#include "commander/parsed_line.h"
#include "commander/hints.h"
#include "test_utils.h"

TEST(test_hints, none_completions)
{
    Hints hints(Parsed_line("pw"), strvec({}));
    EXPECT_EQ(Hints::COLOR_RED, hints.color());
    EXPECT_TRUE(hints.bold());
    EXPECT_EQ(" (INVALID [pw] ())", hints.hint_text());
}


TEST(test_hints, single_prefix_match)
{
    Hints hints(Parsed_line("pw"), strvec({"pwd"}));
    EXPECT_EQ(Hints::COLOR_GREEN, hints.color());
    EXPECT_FALSE(hints.bold());
    EXPECT_EQ("d", hints.hint_text());
}

TEST(test_hints, single_exact_match)
{
    Hints hints(Parsed_line("pwd"), strvec({"pwd"}));
    EXPECT_EQ(Hints::COLOR_GREEN, hints.color());
    EXPECT_FALSE(hints.bold());
    EXPECT_EQ("", hints.hint_text());
}

TEST(test_hints, multi_match_no_common_prefix)
{
    Hints hints(Parsed_line(""), strvec({"abc", "pwd"}));
    EXPECT_EQ(Hints::COLOR_MAGENTA, hints.color());
    EXPECT_FALSE(hints.bold());
    EXPECT_EQ("{abc,pwd}", hints.hint_text());
}

TEST(test_hints, multi_match_common_prefix)
{
    Hints hints(Parsed_line("pw"), strvec({"pwd", "pwe"}));
    EXPECT_EQ(Hints::COLOR_MAGENTA, hints.color());
    EXPECT_FALSE(hints.bold());
    EXPECT_EQ("{d,e}", hints.hint_text());
}

TEST(test_hints, multi_match_one_exact)
{
    // note pwd matches exactly, but there is another option too
    Hints hints(Parsed_line("pwd"), strvec({"pwd", "pwd foo"}));
    EXPECT_EQ(Hints::COLOR_MAGENTA, hints.color());
    EXPECT_FALSE(hints.bold());
    EXPECT_EQ("{ foo}", hints.hint_text());

    // swap order of completions
    hints = Hints(Parsed_line("pwd"), strvec({"pwd foo", "pwd"}));
    EXPECT_EQ(Hints::COLOR_MAGENTA, hints.color());
    EXPECT_FALSE(hints.bold());
    EXPECT_EQ("{ foo}", hints.hint_text()); // expect order to be ordered by shortest
}

TEST(test_hints, multi_match_three)
{
    Hints hints(Parsed_line("pwd"), strvec({"pwd", "pwd fooz", "pwd bar"}));
    EXPECT_EQ(Hints::COLOR_MAGENTA, hints.color());
    EXPECT_FALSE(hints.bold());
    EXPECT_EQ("{ bar, fooz}", hints.hint_text());
}

TEST(test_hints, multi_match_no_space)
{
    Hints hints(Parsed_line("pwd"), strvec({"pwd", "pwdfooz", "pwdbar"}));
    EXPECT_EQ(Hints::COLOR_MAGENTA, hints.color());
    EXPECT_FALSE(hints.bold());
    EXPECT_EQ("{bar,fooz}", hints.hint_text());
}

TEST(test_hints, multi_match_no_space_partial)
{
    Hints hints(Parsed_line("pw"), strvec({"pwd", "pwdfooz", "pwdbar"}));
    EXPECT_EQ(Hints::COLOR_MAGENTA, hints.color());
    EXPECT_FALSE(hints.bold());
    EXPECT_EQ("d{bar,fooz}", hints.hint_text());
}