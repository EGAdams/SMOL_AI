# MODE_1_FUNCTIONS.cpp

## Description
This file contains the implementation of the `Mode1Functions` class. This class is responsible for handling the functionality of mode 1 in a game. It interacts with various other classes and objects to perform tasks such as scoring, undoing moves, updating LEDs, and handling serve actions.

## Dependencies
- `MODE_1_FUNCTIONS.h`: Header file for the `Mode1Functions` class.
- `Arduino.h`: Header file for Arduino platform-specific functions and types.
- `DIGI_V6_15.h`: Header file for a specific hardware interface library.

## Class: Mode1Functions
### Constructor
- Parameters:
  - `Player* player1`: Pointer to the first player object.
  - `Player* player2`: Pointer to the second player object.
  - `PinInterface* pinInterface`: Pointer to the pin interface object.
  - `GameState* gameState`: Pointer to the game state object.
  - `History* history`: Pointer to the history object.
- Description: Initializes the `Mode1Functions` object with the provided player, pin interface, game state, and history objects. It also initializes other member objects such as `Undo`, `PointLeds`, `Mode1Score`, and `ServeLeds`.

### Destructor
- Description: Destroys the `Mode1Functions` object.

### Function: mode1ButtonFunction
- Description: Handles the button press events in mode 1. It performs different actions based on the button pressed by the player.
- Switch Cases:
  - Case 0: No action.
  - Case 1: Player 1 scores a point. It sets the mode 1 undo, updates the player's points, and calls the `playerOneScore` function of the `Mode1Score` object.
  - Case 2: Undo button pressed. It calls the `mode1Undo` function of the `Undo` object.
  - Case 3: Player 2 scores a point. It sets the mode 1 undo, updates the player's points, and calls the `playerTwoScore` function of the `Mode1Score` object.
  - Case 4: Undo button pressed. It calls the `mode1Undo` function of the `Undo` object.
- After performing the action, it resets the player button state to 0.

### Function: mode1ServeFunction
- Description: Handles the serve action in mode 1. It calls the `serveSwitch` function of the `ServeLeds` object.

### Function: pointFlash
- Description: Handles the flashing of LEDs when a player's points exceed a certain threshold. It checks if the point flash flag is set and performs the flashing action accordingly.

# MODE_1_FUNCTIONS.h

## Description
This header file defines the `Mode1Functions` class, which is responsible for handling the functionality of mode 1 in a game. It declares the class members and function prototypes.

## Dependencies
- `Arduino.h`: Header file for Arduino platform-specific functions and types.
- `GameState.h`: Header file for the `GameState` class.
- `GameTimer.h`: Header file for the `GameTimer` class.
- `MODE_1_SCORE.h`: Header file for the `Mode1Score` class.
- `POINT_LEDs.h`: Header file for the `PointLeds` class.
- `PinInterface.h`: Header file for the `PinInterface` class.
- `UNDO.h`: Header file for the `Undo` class.
- `History`: Forward declaration of the `History` class.

## Class: Mode1Functions
### Constructor
- Parameters:
  - `Player* player1`: Pointer to the first player object.
  - `Player* player2`: Pointer to the second player object.
  - `PinInterface* pinInterface`: Pointer to the pin interface object.
  - `GameState* gameState`: Pointer to the game state object.
  - `History* history`: Pointer to the history object.
- Description: Initializes the `Mode1Functions` object with the provided player, pin interface, game state, and history objects.

### Destructor
- Description: Destroys the `Mode1Functions` object.

### Function: mode1ButtonFunction
- Description: Handles the button press events in mode 1.

### Function: mode1ServeFunction
- Description: Handles the serve action in mode 1.

### Function: pointFlash
- Description: Handles the flashing of LEDs when a player's points exceed a certain threshold.