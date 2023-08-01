#include "PinInterface.h"
#include <gtest/gtest.h>

class PinInterfaceTest : public ::testing::Test {  // Define a test fixture
protected:
    PinState*                   pinState;
    std::map<std::string, int>  pinMap;
    PinInterface*               pinInterface;

    void SetUp() override {
        pinState         = new PinState( pinMap );
        pinInterface     = new PinInterface( pinState ); }

    void TearDown() override {
        delete pinInterface;
        delete pinState; }};

TEST_F( PinInterfaceTest, TestAnalogRead ) {  // Define tests
    int pin = 5;
    int value = 1;
    pinInterface->pinAnalogWrite( pin, value );
    EXPECT_EQ( pinInterface->pinAnalogRead( pin ), value );}

TEST_F( PinInterfaceTest, TestDigitalRead ) {
    int pin = 5;
    int value = 1; // Digital pins can only be HIGH ( 1 ) or LOW (0)
    pinInterface->pinDigitalWrite( pin, value );

    EXPECT_EQ( pinInterface->pinDigitalRead( pin ), value );}

TEST_F( PinInterfaceTest, TestAnalogWrite ) {
    int pin = 5;
    int value = 1;
    pinInterface->pinAnalogWrite( pin, value );
    EXPECT_EQ( pinState->getPinState(std::to_string( pin )), value );}

TEST_F( PinInterfaceTest, TestDigitalWrite ) {
    int pin = 5;
    int value = 1; // Digital pins can only be HIGH ( 1 ) or LOW (0)
    pinInterface->pinDigitalWrite( pin, value );
    EXPECT_EQ( pinState->getPinState(std::to_string( pin )), value );}
