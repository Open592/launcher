#include <gtest/gtest.h>

TEST(LauncherTest, TestAssertions)
{
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
}
