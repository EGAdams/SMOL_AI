Act as a world-class, super-intelligent C++ Developer who always follows the SOLID principles of software design and is an expert at simplifying problems using Object-Oriented programming designs.

In addition to writing the code described below, please also use the Google Test Framework and write unit tests for each object.  Create interfaces for objects that need to be mocked.

# MODE_1_FUNCTIONS.cpp

This file contains the implementation of the `Mode1Functions` class. The class has a constructor that takes in several objects as parameters, including `Player`, `PinInterface`, `GameState`, and `History`. It initializes member variables `_player1`, `_player2`, `_gameState`, `_history`, `_undo`, `_pointLeds`, `_mode1Score`, and `_serveLeds` with the corresponding parameters.

The destructor is empty and does not perform any specific actions.

## mode1ButtonFunction()

This function is responsible for handling button presses in mode 1. It uses a switch statement to determine the action based on the value of `_gameState->getPlayerButton()`. 

- Case 0: No action is taken.
- Case 1: Player 1 scores a point. It sets the mode 1 undo, checks if point flashing is enabled, updates the player points, delays the game, updates the undo memory, and calls the `mode1P1Score()` function of `_mode1Score`.
- Case 2: Undo button is pressed. It delays the game and calls the `mode1Undo()` function of `_undo`.
- Case 3: Player 2 scores a point. It sets the mode 1 undo, checks if point flashing is enabled, updates the player points, delays the game, updates the undo memory, and calls the `mode1P2Score()` function of `_mode1Score`.
- Case 4: Undo button is pressed. It delays the game and calls the `mode1Undo()` function of `_undo`.

After performing the corresponding action, it sets `_gameState->setPlayerButton(0)` to reset the button state.

## mode1ServeFunction()

This function is responsible for handling the serve action in mode 1. It sets the mode 1 undo and calls the `serveSwitch()` function of `_serveLeds`.

## pointFlash()

This function is responsible for handling the point flashing feature in mode 1. If point flashing is enabled, it checks the points of both players. If a player has more than 3 points, it performs the following actions:

- For player 1: If running on Windows, it sets the points to 99 and updates the point LEDs. Otherwise, it checks the time difference between the current time and the previous time. If the difference is greater than the flash delay, it toggles the 4th LED on and off by setting the points to the stored value or 99, respectively. It updates the point LEDs and updates the previous time.
- For player 2: Same logic as player 1.

# MODE_1_FUNCTIONS.h

This header file defines the `Mode1Functions` class. It includes several other header files, such as "Arduino.h", "GameState.h", "GameTimer.h", "MODE_1_SCORE.h", "POINT_LEDs.h", "PinInterface.h", and "UNDO.h". It also forward declares the `History` class.

The `Mode1Functions` class has a public constructor that takes in `Player`, `PinInterface`, `GameState`, and `History` objects as parameters. It also has a public destructor.

The public member functions include:
- `mode1ButtonFunction()`: Handles button presses in mode 1.
- `mode1ServeFunction()`: Handles the serve action in mode 1.
- `pointFlash()`: Handles the point flashing feature in mode 1.

The private member variables include:
- `_player1`: Pointer to the `Player` object for player 1.
- `_player2`: Pointer to the `Player` object for player 2.
- `_gameState`: Pointer to the `GameState` object.
- `_history`: Pointer to the `History` object.
- `_undo`: An instance of the `Undo` class.
- `_pointLeds`: An instance of the `PointLeds` class.
- `_mode1Score`: An instance of the `Mode1Score` class.
- `_serveLeds`: An instance of the `ServeLeds` class.

Note: The specific implementation of the `Player`, `PinInterface`, `GameState`, `History`, `Undo`, `PointLeds`, `Mode1Score`, and `ServeLeds` classes are not provided in the given files.

# Unit Testing for MODE_1_FUNCTIONS
Unit testing is an essential part of software development that ensures the correctness of individual units of source code. This section details the various unit tests that should be performed on the MODE_1_FUNCTIONS class.

# Test Case Class
Firstly, a test case class should be created, Mode1FunctionsTest, which will contain all the unit test methods for Mode1Functions. This test class should include the same dependencies as Mode1Functions, along with a testing library (like GoogleTest).

```cpp
#include "gtest/gtest.h"
#include "Mode1Functions.h"
// Include other necessary files...

class Mode1FunctionsTest : public ::testing::Test {
protected:
    // SetUp and TearDown functions...
};
```

# Test Cases
Test Case: Constructor and Destructor
This test case verifies that the constructor correctly initializes all member variables and the destructor cleans up properly. Mock objects should be passed to the constructor and it should be checked whether these mock objects are correctly assigned to the member variables.

## Test Case: mode1ButtonFunction()
This function should be tested with each possible case in the switch statement. The test should verify that the correct actions are taken based on the value of _gameState->getPlayerButton(). It should also check that _gameState->setPlayerButton(0) is called at the end of each case.

## Test Case: mode1ServeFunction()
This test case should verify that the serveSwitch() function of _serveLeds is called correctly when mode1ServeFunction() is invoked.

## Test Case: pointFlash()
This function should be tested with various point values for both players. The test should verify that the correct LED actions are taken based on the points of the players. It should also check the correct toggling of the 4th LED on and off when the flash delay is surpassed.

# Mock Objects
For these unit tests to be carried out properly, mock objects of the Player, PinInterface, GameState, History, Undo, PointLeds, Mode1Score, and ServeLeds classes should be created. These mock objects should mimic the behavior of the real objects but should be controllable by the test cases.