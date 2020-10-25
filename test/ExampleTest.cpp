#include <gtest/gtest.h>
#include "../src/Example.hpp"

// Will find the header, because we've linked the gtest main

bool f() {
    return true;
}

TEST(ExampleTests, SanityCheck) { // Test(<SuiteName>, <TestName>)
    EXPECT_TRUE(true); // A test will run all expects
    ASSERT_TRUE(true); // Asserts shortcircuit the test
    EXPECT_TRUE(f()); // local functions can be used
}

TEST(ExampleTests, ExternalCode) {
    EXPECT_EQ(foo(1, 2), 3);
}
