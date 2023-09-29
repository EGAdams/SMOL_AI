# Mode1Score.cpp

## Class: Mode1Score

### Constructor:
- Parameters:
  - player1: IPlayer*
  - player2: IPlayer*
  - pinInterface: PinInterface*
  - gameState: GameState*
  - history: History*
- Initializes the member variables with the provided parameters.
- Initializes the following member objects:
  - _mode1TieBreaker: TieBreaker
  - _pointLeds: PointLeds
  - _gameLeds: GameLeds
  - _setLeds: SetLeds
  - _mode1WinSequences: WinSequences
  - _undo: Undo

### Destructor:
- Does nothing.

### Method: setScoreBoard
- Parameters:
  - scoreBoard: ScoreBoard*
- Calls the corresponding method on the member objects _pointLeds, _gameLeds, _mode1WinSequences, and _setLeds, passing the scoreBoard parameter.

### Method: _resetGame
- Resets the game state:
  - Delays the game for a certain duration.
  - Sets the points of player1 and player2 to 0.
  - Sets the serve switch to 1.
  - Sets the serve to 0.
  - Calls the updatePoints method on the _pointLeds object.

### Method: updateScore
- Parameters:
  - currentPlayer: IPlayer*
- Updates the score based on the current player's points:
  - If the current player has 3 or more points:
    - If the current player's points are equal to the opponent's points, set both players' points to 3.
    - If the current player's points are greater than 3 and the point difference is more than 1, increment the current player's games, call the memory method on the _undo object, and call the mode1P1Games or mode1P2Games method based on the current player's number.
    - If the current player's points are equal to 4, set the point flash to 1, set the previous time to the current game time, and set the toggle to 0.
  - Calls the updatePoints method on the _pointLeds object.

### Method: playerOneScore
- Calls the updateScore method with player1 as the parameter.

### Method: playerTwoScore
- Calls the updateScore method with player2 as the parameter.

### Method: mode1P1Games
- Updates the games for player1:
  - Increments the serve switch.
  - If player1 has won enough games to win a set:
    - If both player1 and player2 have won the same number of games, enable the tie break and call the p1TBSetWinSequence method on the _mode1WinSequences object.
    - If the tie break is not enabled, check if the difference between player1's games and player2's games is more than 1. If true, increment player1's sets, update the sets on the _setLeds object, and call the p1SetWinSequence method on the _mode1WinSequences object.
    - If player1 has won 7 games, call the p1MatchWinSequence method on the _mode1WinSequences object and stop the game running.
    - Otherwise, increment the current set, call the p1SetWinSequence method on the _mode1WinSequences object, update the sets on the _setLeds object, delay the game for a certain duration, and reset the game.
  - If player1 has not won enough games to win a set, call the p1GameWinSequence method on the _mode1WinSequences object and reset the game.

### Method: mode1P2Games
- Updates the games for player2:
  - Increments the serve switch.
  - If player2 has won enough games to win a set:
    - If both player1 and player2 have won the same number of games, enable the tie break and call the p2TBSetWinSequence method on the _mode1WinSequences object.
    - If the tie break is not enabled, check if the difference between player2's games and player1's games is more than 1. If true, increment player2's sets, update the sets on the _setLeds object, and call the p2SetWinSequence method on the _mode1WinSequences object.
    - If player2 has won 7 games, call the p2MatchWinSequence method on the _mode1WinSequences object and stop the game running.
    - Otherwise, increment the current set, call the p2SetWinSequence method on the _mode1WinSequences object, update the sets on the _setLeds object, delay the game for a certain duration, and reset the game.
  - If player2 has not won enough games to win a set, call the p2GameWinSequence method on the _mode1WinSequences object and reset the game.

### Method: mode1TBP1Games
- Updates the games for player1 during a tie break:
  - Updates the games on the _gameLeds object.
  - Increments the serve switch.
  - Delays the game for a certain duration.
  - If player1 has won 15 games, increment player1's sets and check if player1 has won enough sets to win the match:
    - If player1 has won the same number of sets as player2, enable the tie break, call the p1TBSetWinSequence method on the _mode1WinSequences object, and enable the tie break on the _mode1TieBreaker object.
    - Otherwise, increment the current set, call the p1SetWinSequence method on the _mode1WinSequences object, and end the tie break on the _mode1TieBreaker object.
  - If player1 has won 10 or more games and the point difference is more than 1, increment player1's sets and check if player1 has won enough sets to win the match:
    - If player1 has won the same number of sets as player2, enable the tie break, call the p1TBSetWinSequence method on the _mode1WinSequences object, and enable the tie break on the _mode1TieBreaker object.
    - Otherwise, increment the current set, call the p1SetWinSequence method on the _mode1WinSequences object, and end the tie break on the _mode1TieBreaker object.

### Method: mode1SetTBP1Games
- Updates the games for player1 during a tie break in a set:
  - Updates the games on the _gameLeds object.
  - Delays the game for a certain duration.
  - If player1 has won 7 games, increment player1's sets, update the sets on the _setLeds object, call the p1SetTBWinSequence method on the _mode1WinSequences object, turn off the tie LEDs on the _mode1TieBreaker object, call the p1MatchWinSequence method on the _mode1WinSequences object, and stop the game running.
  - Increments the serve switch.

### Method: mode1TBP2Games
- Updates the games for player2 during a tie break:
  - Updates the games on the _gameLeds object.
  - Increments the serve switch.
  - Delays the game for a certain duration.
  - If player2 has won 15 games, increment player2's sets and check if player2 has won enough sets to win the match:
    - If player2 has won the same number of sets as player1, enable the tie break, call the p2TBSetWinSequence method on the _mode1WinSequences object, and enable the tie break on the _mode1TieBreaker object.
    - Otherwise, increment the current set, call the p2SetWinSequence method on the _mode1WinSequences object, and end the tie break on the _mode1TieBreaker object.
  - If player2 has won 10 or more games and the point difference is more than 1, increment player2's sets and check if player2 has won enough sets to win the match:
    - If player2 has won the same number of sets as player1, enable the tie break, call the p2TBSetWinSequence method on the _mode1WinSequences object, and enable the tie break on the _mode1TieBreaker object.
    - Otherwise, increment the current set, call the p2SetWinSequence method on the _mode1WinSequences object, and end the tie break on the _mode1TieBreaker object.

### Method: mode1SetTBP2Games
- Updates the games for player2 during a tie break in a set:
  - Updates the games on the _gameLeds object.
  - Delays the game for a certain duration.
  - If player2 has won 7 games, increment player2's sets, update the sets on the _setLeds object, call the p2SetTBWinSequence method on the _mode1WinSequences object, turn off the tie LEDs on the _mode1TieBreaker object, call the p2MatchWinSequence method on the _mode1WinSequences object, and stop the game running.
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
- Tests the playerOneScore method when player1 has more than 3 points and the point difference with player2 is more than 1.
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
  - player1: IPlayer*
  - player2: IPlayer*
  - pinInterface: PinInterface*
  - gameState: GameState*
  - history: History*
- Initializes the member variables with the provided parameters.
- Initializes the following
