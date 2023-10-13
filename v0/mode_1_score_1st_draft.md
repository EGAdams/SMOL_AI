# Mode1Score.cpp

## Class: Mode1Score

### Constructor:
- Parameters:
  - player1: IPlayer* (pointer to the first player)
  - player2: IPlayer* (pointer to the second player)
  - pinInterface: PinInterface* (pointer to the pin interface)
  - gameState: GameState* (pointer to the game state)
  - history: History* (pointer to the history)
- Initializes the member variables with the provided parameters.
- Initializes the following member objects:
  - _mode1TieBreaker: TieBreaker (initialized with player1, player2, pinInterface, gameState, and history)
  - _pointLeds: PointLeds (initialized with player1, player2, and pinInterface)
  - _gameLeds: GameLeds (initialized with player1, player2, and pinInterface)
  - _setLeds: SetLeds (initialized with player1, player2, and pinInterface)
  - _mode1WinSequences: WinSequences (initialized with player1, player2, pinInterface, and gameState)
  - _undo: Undo (initialized with player1, player2, pinInterface, and gameState)

### Destructor:
- Does nothing.

### Method: setScoreBoard
- Parameters:
  - scoreBoard: ScoreBoard* (pointer to the score board)
- Calls the corresponding setScoreBoard method on the following member objects:
  - _pointLeds
  - _gameLeds
  - _mode1WinSequences
  - _setLeds

### Method: _resetGame
- Resets the game state:
  - Delays the game for a certain duration.
  - Sets the points of player1 and player2 to 0.
  - Sets the serve switch to 1.
  - Sets the serve to 0.
  - Updates the point LEDs.

### Method: updateScore
- Parameters:
  - currentPlayer: IPlayer* (pointer to the current player)
- Updates the score based on the current player's points:
  - If the current player has 3 or more points:
    - If the current player's points are equal to the opponent's points, set both players' points to 3.
    - If the current player's points are greater than 3 and the point difference is more than 1, increment the current player's games, call the _undo.memory() method, and call the corresponding playerOneGameWin() or playerTwoGameWin() method based on the current player's number.
    - If the current player's points are equal to 4, set the game state's point flash to 1, set the previous time to the current game time, and set the toggle to 0.
  - Updates the point LEDs.

### Method: playerOneScore
- Calls the updateScore method with player1 as the current player.

### Method: playerTwoScore
- Calls the updateScore method with player2 as the current player.

### Method: playerOneGameWin
- Updates the game state and player1's games:
  - Increments the serve switch.
  - If player1 has won enough games to win a set:
    - If both player1 and player2 have won the same number of games, enable the tie break and call the corresponding p1TBSetWinSequence() method.
    - If the tie break is not enabled, check if player1 has won the set by a margin of 2 games. If so, increment player1's sets, update the set LEDs, and call the corresponding p1SetWinSequence() method.
    - If player1 has won enough sets to win the match, call the corresponding p1MatchWinSequence() method and stop the game running.
    - Otherwise, call the corresponding p1GameWinSequence() method and reset the game.
  - If player1 has not won enough games to win a set, call the corresponding p1GameWinSequence() method and reset the game.

### Method: playerTwoGameWin
- Updates the game state and player2's games:
  - Increments the serve switch.
  - If player2 has won enough games to win a set:
    - If both player1 and player2 have won the same number of games, enable the tie break and call the corresponding p2TBSetWinSequence() method.
    - If the tie break is not enabled, check if player2 has won the set by a margin of 2 games. If so, increment player2's sets, update the set LEDs, and call the corresponding p2SetWinSequence() method.
    - If player2 has won enough sets to win the match, call the corresponding p2MatchWinSequence() method and stop the game running.
    - Otherwise, call the corresponding p2GameWinSequence() method and reset the game.
  - If player2 has not won enough games to win a set, call the corresponding p2GameWinSequence() method and reset the game.

### Method: mode1TBP1Games
- Updates the game state and player1's games during a tie break:
  - Updates the game LEDs.
  - Increments the serve switch.
  - If player1 has won 15 games, check if player1 has won the set or the match:
    - If player1 has won enough sets to win the match, call the corresponding p1MatchWinSequence() method and stop the game running.
    - Otherwise, increment player1's sets, update the set LEDs, and call the corresponding p1SetWinSequence() method.
  - If player1 has won 10 or more games and the point difference is more than 1, increment player1's sets, update the set LEDs, and call the corresponding p1SetWinSequence() method.

### Method: mode1SetTBP1Games
- Updates the game state and player1's games during a tie break in the last set:
  - Updates the game LEDs.
  - Delays the game for a certain duration.
  - If player1 has won 7 games, increment player1's sets, update the set LEDs, call the corresponding p1SetTBWinSequence() method, turn off the tie LEDs, call the corresponding p1MatchWinSequence() method, and stop the game running.
  - Increments the serve switch.

### Method: mode1TBP2Games
- Updates the game state and player2's games during a tie break:
  - Updates the game LEDs.
  - Increments the serve switch.
  - If player2 has won 15 games, check if player2 has won the set or the match:
    - If player2 has won enough sets to win the match, call the corresponding p2MatchWinSequence() method and stop the game running.
    - Otherwise, increment player2's sets, update the set LEDs, and call the corresponding p2SetWinSequence() method.
  - If player2 has won 10 or more games and the point difference is more than 1, increment player2's sets, update the set LEDs, and call the corresponding p2SetWinSequence() method.

### Method: mode1SetTBP2Games
- Updates the game state and player2's games during a tie break in the last set:
  - Updates the game LEDs.
  - Delays the game for a certain duration.
  - If player2 has won 7 games, increment player2's sets, update the set LEDs, call the corresponding p2SetTBWinSequence() method, turn off the tie LEDs, call the corresponding p2MatchWinSequence() method, and stop the game running.
  - Increments the serve switch.

## Class: MockPlayer
- Inherits from Player class.
- Mocks the methods of the Player class.

## Class: MockPinInterface
- Inherits from PinInterface class.
- Mocks the methods of the PinInterface class.

## Class: MockGameState
- Inherits from GameState class.
- Mocks the methods of the GameState class.

## Class: MockHistory
- Inherits from History class.
- Mocks the methods of the History class.

## Class: Mode1ScoreTest
- Inherits from ::testing::Test class.
- Contains test cases for the Mode1Score class.

### Test Case: TestMode1P1Score_LessThan3Points
- Tests the playerOneScore method when player1 has less than 3 points.
- Sets up the necessary expectations.
- Calls the playerOneScore method.
- Asserts the expected behavior.

### Test Case: TestMode1P1Score_3Points_LessThan3PointsP2
- Tests the playerOneScore method when player1 has 3 points and player2 has less than 3 points.
- Sets up the necessary expectations.
- Calls the playerOneScore method.
- Asserts the expected behavior.

### Test Case: TestMode1P1Score_3Points_EqualPoints
- Tests the playerOneScore method when player1 has 3 points and player2 has 3 points.
- Sets up the necessary expectations.
- Calls the playerOneScore method.
- Asserts the expected behavior.

### Test Case: TestMode1P1Score_MoreThan3Points_DifferenceMoreThan1
- Tests the playerOneScore method when player1 has more than 3 points and the point difference is more than 1.
- Sets up the necessary expectations.
- Calls the playerOneScore method.
- Asserts the expected behavior.

### Test Case: TestMode1P1Score_4Points
- Tests the playerOneScore method when player1 has 4 points.
- Sets up the necessary expectations.
- Calls the playerOneScore method.
- Asserts the expected behavior.

# Mode1Score.h

## Class: Mode1Score

### Constructor:
- Parameters:
  - player1: IPlayer* (pointer to the first player)
  - player2: IPlayer* (pointer to the second player)
  - pinInterface: PinInterface* (pointer to the pin interface)
  - gameState: GameState* (pointer to the game state)
  - history: History* (pointer to the history)
- Initializes the member variables with the provided parameters.

### Method: playerOneScore
- Updates the score for player1.

### Method: playerOneGameWin
- Updates the game state and player1's games.

### Method: mode1TBP1Games
- Updates the game state and player1's games during a tie break.

### Method: mode1SetTBP1Games
- Updates the game state and player1's games during a tie break in the last set.

### Method: playerTwoScore
- Updates the score for player2.

### Method: playerTwoGameWin
- Updates the game state and player2's games.

### Method: mode1TBP2Games
- Updates the game state and player2's games during a tie break.

### Method: mode1SetTBP2Games
- Updates the game state and player2's games during a tie break in the last set.

### Method: setScoreBoard
- Parameters:
  - scoreBoard: ScoreBoard* (pointer to the score board)
- Sets the score board for the following member objects:
  - _pointLeds
  - _gameLeds
  - _mode1WinSequences
  - _setLeds

### Method: updateScore
- Parameters:
  - currentPlayer: IPlayer* (pointer to the current player)
- Updates the score based on the current player's points.

## Class: MockPlayer
- Inherits from Player class.
- Mocks the methods of the Player class.

## Class: MockPinInterface
- Inherits from PinInterface class.
- Mocks the methods of the PinInterface class.

## Class: MockGameState
- Inherits from GameState class.
- Mocks the methods of the GameState class.

## Class: