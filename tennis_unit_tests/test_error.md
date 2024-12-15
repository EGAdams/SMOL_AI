I am getting the following error when running:
``` command
    ./MockPinInterfaceTest
```

``` output
./MockPinInterfaceTest 
Running main() from /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/googletest/src/gtest_main.cc
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from PinInterfaceTest
[ RUN      ] PinInterfaceTest.TestAnalogRead
[       OK ] PinInterfaceTest.TestAnalogRead (0 ms)
[ RUN      ] PinInterfaceTest.TestDigitalRead
[       OK ] PinInterfaceTest.TestDigitalRead (0 ms)
[ RUN      ] PinInterfaceTest.TestAnalogWrite
pinState: translated constant: P2_GAMES_LED1
0
translated constant: P2_GAMES_LED1
MockPinInterface.cpp:69: Failure
Expected equality of these values:
  pinState->getPinState(std::to_string(pin))
    Which is: 0
  value
    Which is: 1

MockPinInterface.cpp:64: Failure
Actual function call count doesn't match EXPECT_CALL(*mockPinInterface, pinAnalogWrite(pin, value))...
         Expected: to be called once
           Actual: never called - unsatisfied and active

[  FAILED  ] PinInterfaceTest.TestAnalogWrite (0 ms)
[ RUN      ] PinInterfaceTest.TestDigitalWrite
pinState: translated constant: P2_GAMES_LED1
0
translated constant: P2_GAMES_LED1
MockPinInterface.cpp:81: Failure
Expected equality of these values:
  pinState->getPinState(std::to_string(pin))
    Which is: 0
  value
    Which is: 1

MockPinInterface.cpp:76: Failure
Actual function call count doesn't match EXPECT_CALL(*mockPinInterface, pinDigitalWrite(pin, value))...
         Expected: to be called once
           Actual: never called - unsatisfied and active

[  FAILED  ] PinInterfaceTest.TestDigitalWrite (0 ms)
[----------] 4 tests from PinInterfaceTest (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (1 ms total)
[  PASSED  ] 2 tests.
[  FAILED  ] 2 tests, listed below:
[  FAILED  ] PinInterfaceTest.TestAnalogWrite
[  FAILED  ] PinInterfaceTest.TestDigitalWrite

 2 FAILED TESTS
```