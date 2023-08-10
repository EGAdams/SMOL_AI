#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IPinInterfaceMock.h"
#include "../PinState/IPinStateMock.h"

class PinInterfaceTest : public ::testing::Test {  // Define a test fixture
protected:
    IPinInterfaceMock* mockPinInterface;
    IPinStateMock*     mockPinState;

    void SetUp() override {
        mockPinState = new IPinStateMock();
        mockPinInterface = new IPinInterfaceMock();
    }

    void TearDown() override {
        delete mockPinInterface;
        delete mockPinState;
    }
};

TEST_F(PinInterfaceTest, TestAnalogRead) {  // Define tests
    int pin = 5;
    int value = 1;

    // Set expectation for the mock objects
    EXPECT_CALL(*mockPinInterface, pinAnalogWrite(pin, value));
    EXPECT_CALL(*mockPinState, getPinState(std::to_string(pin))).WillOnce(::testing::Return(value));

    mockPinInterface->pinAnalogWrite(pin, value);
    EXPECT_EQ(mockPinInterface->pinAnalogRead(pin), value);
}

TEST_F(PinInterfaceTest, TestDigitalRead) {
    int pin = 5;
    int value = 1; // Digital pins can only be HIGH (1) or LOW (0)

    // Set expectation for the mock objects
    EXPECT_CALL(*mockPinInterface, pinDigitalWrite(pin, value));
    EXPECT_CALL(*mockPinState, getPinState(std::to_string(pin))).WillOnce(::testing::Return(value));

    mockPinInterface->pinDigitalWrite(pin, value);
    EXPECT_EQ(mockPinInterface->pinDigitalRead(pin), value);
}

TEST_F(PinInterfaceTest, TestAnalogWrite) {
    int pin = 5;
    int value = 1;

    // Set expectation for the mock objects
    EXPECT_CALL(*mockPinState, setPinState(std::to_string(pin), value));
    mockPinInterface->pinAnalogWrite(pin, value);
}

TEST_F(PinInterfaceTest, TestDigitalWrite) {
    int pin = 5;
    int value = 1; // Digital pins can only be HIGH (1) or LOW (0)

    // Set expectation for the mock objects
    EXPECT_CALL(*mockPinState, setPinState(std::to_string(pin), value));
    mockPinInterface->pinDigitalWrite(pin, value);
}
