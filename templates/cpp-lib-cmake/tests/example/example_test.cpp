#include <example/example.h>
#include <gtest/gtest.h>

using example::fibonacci;

TEST(example, fibonacci) {
    ASSERT_EQ(fibonacci(0), 0u);
    ASSERT_EQ(fibonacci(1), 1u);
    ASSERT_EQ(fibonacci(2), 1u);
    ASSERT_EQ(fibonacci(3), 2u);
    ASSERT_EQ(fibonacci(4), 3u);
    ASSERT_EQ(fibonacci(5), 5u);
    ASSERT_EQ(fibonacci(6), 8u);
    ASSERT_EQ(fibonacci(7), 13u);
}
