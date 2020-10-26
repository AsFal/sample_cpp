#include <gtest/gtest.h>
// Will find the header, because we've linked the gtest main

bool f() {
    return true;
}

// test that the proper files are begin generated
// to have automated tests, seperate getting the rectangles in another step
// conditions around file access


TEST(ExampleTests, SanityCheck) { // Test(<SuiteName>, <TestName>)
    EXPECT_TRUE(true); // A test will run all expects
    ASSERT_TRUE(true); // Asserts shortcircuit the test
    EXPECT_TRUE(f()); // local functions can be used
}
