#include "gtest/gtest.h"
#include <string>
#include <vector>

typedef std::vector<std::string> strvec;


#define EXPECT_THROW_WITH_MESSAGE(__statement, __message)\
try { (__statement);\
      FAIL() << "Expected exception with message " << (__message)\
            << ". actual result is none thrown."; \
} catch (std::exception &e) {\
    EXPECT_EQ(std::string(__message), std::string(e.what())) << "unexpected message on thrown exception.";\
}

std::string to_string(const std::vector<std::string> &v);
