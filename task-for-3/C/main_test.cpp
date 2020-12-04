#include <gtest/gtest.h>

#include "A/index.h"
#include "B/lib.h"

TEST(A, Add) {
    ASSERT_EQ(add(1, 2), 3);
    ASSERT_EQ(add(1, -2), -1);
}

TEST(A, Substract) {
    ASSERT_EQ(substract(1, 2), -1);
    ASSERT_EQ(substract(1, -2), 3);
}

TEST(A, Multiply) {
    ASSERT_EQ(multiply(1, 2), 2);
    ASSERT_EQ(multiply(1, -2), -2);
}
