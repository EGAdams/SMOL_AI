#pragma once

#include <map>
#include <string>
#include "../PinState/PinState.h"

class IPinInterface {
public:
    virtual ~IPinInterface() = default;

    // Pure virtual functions based on PinInterface.h
    virtual void pinAnalogWrite(int pin, int value) = 0;
    virtual void pinDigitalWrite(int pin, int value) = 0;
    virtual int pinAnalogRead(int pin) = 0;
    virtual int pinDigitalRead(int pin) = 0;
    virtual std::map<std::string, int> getPinStateMap() = 0;
};
