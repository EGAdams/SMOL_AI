#include "Mode1Score.h"
#include <gtest/gtest.h>

// Define a test fixture class template
class Mode1ScoreTest : public ::testing::Test {
protected:
    // Objects declared here can be used by all tests in the test case for Mode1Score
    Mode1Score* score;

    Mode1ScoreTest() {
        // Initialize the Mode1Score object before each test
        score = new Mode1Score(nullptr, nullptr, nullptr, nullptr, nullptr);
    }

    virtual ~Mode1ScoreTest() {
        // Code here will be called immediately after each test (right before the destructor)
        delete score;
    }
};

// Test case must be called the class, also you can use '_' instead of spaces
TEST_F(Mode1ScoreTest, Mode1P1ScoreTest) {
    // You can access data in the test fixture here
    // ASSERT_NO_THROW(score->mode1P1Score());
}

// You can add more tests to this test case
