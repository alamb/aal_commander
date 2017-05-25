#include "gtest/gtest.h"
#include <string>

#define EXPECT_THROW_WITH_MESSAGE(__statement, __message)\
try { (__statement);\
      FAIL() << "Expected exception with message " << (__message)\
            << ". actual result is none thrown."; \
} catch (std::exception &e) {\
    EXPECT_EQ(std::string(__message), std::string(e.what())) << "unexpected message on thrown exception.";\
}


