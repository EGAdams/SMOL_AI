#include "PinInterface.h"
#include <gmock/gmock.h>

// Create the MOCK class for PinInterface
class MockPinInterface : public PinInterface {
public:
    // Use the constructor of the base class
    using PinInterface::PinInterface;

    // MOCK methods to override the original ones
    MOCK_METHOD(int, pinAnalogRead, (int pin), (override));
    MOCK_METHOD(int, pinDigitalRead, (int pin), (override));
    MOCK_METHOD(void, pinAnalogWrite, (int pin, int value), (override));
    MOCK_METHOD(void, pinDigitalWrite, (int pin, int value), (override));
};

// Define a test fixture
class PinInterfaceTest : public ::testing::Test {
protected:
    MockPinInterface* mockPinInterface;
    PinState* pinState;
    std::map<std::string, int> pinMap;

    void SetUp() override {
        pinState = new PinState(pinMap);
        mockPinInterface = new MockPinInterface(pinState);
    }

    void TearDown() override {
        delete mockPinInterface;
        delete pinState;
    }
};

// Define tests
TEST_F(PinInterfaceTest, TestAnalogRead) {
    int pin = 5;
    int value = 123;
    pinMap[std::to_string(pin)] = value;

    EXPECT_CALL(*mockPinInterface, pinAnalogRead(pin))
        .Times(1)
        .WillOnce(::testing::Return(value));

    EXPECT_EQ(mockPinInterface->pinAnalogRead(pin), value);
}

TEST_F(PinInterfaceTest, TestDigitalRead) {
    int pin = 5;
    int value = 1; // Digital pins can only be HIGH (1) or LOW (0)
    pinMap[std::to_string(pin)] = value;

    EXPECT_CALL(*mockPinInterface, pinDigitalRead(pin))
        .Times(1)
        .WillOnce(::testing::Return(value));

    EXPECT_EQ(mockPinInterface->pinDigitalRead(pin), value);
}

TEST_F(PinInterfaceTest, TestAnalogWrite) {
    int pin = 5;
    int value = 123;

    EXPECT_CALL(*mockPinInterface, pinAnalogWrite(pin, value))
        .Times(1);

    mockPinInterface->pinAnalogWrite(pin, value);
    EXPECT_EQ(pinState->getPinState(std::to_string(pin)), value);
}

TEST_F(PinInterfaceTest, TestDigitalWrite) {
    int pin = 5;
    int value = 1; // Digital pins can only be HIGH (1) or LOW (0)

    EXPECT_CALL(*mockPinInterface, pinDigitalWrite(pin, value))
        .Times(1);

    mockPinInterface->pinDigitalWrite(pin, value);
    EXPECT_EQ(pinState->getPinState(std::to_string(pin)), value);
}
