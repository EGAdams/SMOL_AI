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

// Define a test fixture (if needed)
class PinInterfaceTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up any common data or configuration for your tests
    }

    void TearDown() override {
        // Clean up after your tests (if needed)
    }

    // Add other helper methods or variables specific to your test suite
};
