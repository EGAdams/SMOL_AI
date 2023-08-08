#pragma once

#include <gmock/gmock.h>
#include "IPinInterface.h"

class IPinInterfaceMock : public IPinInterface {
public:
    virtual ~IPinInterfaceMock() = default;

    // Mock methods based on IPinInterface.h
    MOCK_METHOD(void, pinAnalogWrite, (int pin, int value), (override));
    MOCK_METHOD(void, pinDigitalWrite, (int pin, int value), (override));
    MOCK_METHOD(int, pinAnalogRead, (int pin), (override));
    MOCK_METHOD(int, pinDigitalRead, (int pin), (override));
    MOCK_METHOD((std::map<std::string, int>), getPinStateMap, (), (override));
};