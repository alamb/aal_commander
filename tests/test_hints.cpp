#include "gtest/gtest.h"
#include "parsed_line.h"
#include "hints.h"

typedef std::vector<std::string> strvec;

TEST(test_hints, no_completions)
{
    Hints hints(Parsed_line("pw"), strvec({}));
    EXPECT_EQ(Hints::COLOR_RED, hints.color());
    EXPECT_TRUE(hints.bold());
    EXPECT_EQ(" (INVALID [pw] ())", hints.hint_text());
}


TEST(test_hints, prefix_match)
{
    Hints hints(Parsed_line("pw"), strvec({"pwd"}));
    EXPECT_EQ(Hints::COLOR_GREEN, hints.color());
    EXPECT_FALSE(hints.bold());
    EXPECT_EQ("d", hints.hint_text());
}

TEST(test_hints, exact_match)
{
    Hints hints(Parsed_line("pwd"), strvec({"pwd"}));
    EXPECT_EQ(Hints::COLOR_GREEN, hints.color());
    EXPECT_FALSE(hints.bold());
    EXPECT_EQ("", hints.hint_text());
}