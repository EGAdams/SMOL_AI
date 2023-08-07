# Mode1Score.cpp

This file contains the implementation of the `Mode1Score` class.

## Class Definition

### `Mode1Score`

#### Constructors

- `Mode1Score(IPlayer* player1, IPlayer* player2, PinInterface* pinInterface, GameState* gameState, History* history)`: Constructs a `Mode1Score` object with the given player objects, pin interface, game state, and history.

#### Destructor

- `~Mode1Score()`: Destructs the `Mode1Score` object.

#### Public Methods

- `void setScoreBoard(ScoreBoard* scoreBoard)`: Sets the score board for the `Mode1Score` object.
- `void updateScore(IPlayer* currentPlayer)`: Updates the score for the current player.
- `void mode1P1Score()`: Updates the score for player 1.
- `void mode1P2Score()`: Updates the score for player 2.
- `void mode1P1Games()`: Updates the games for player 1.
- `void mode1P2Games()`: Updates the games for player 2.
- `void mode1TBP1Games()`: Updates the games for player 1 in tie-break mode.
- `void mode1SetTBP1Games()`: Updates the games for player 1 in set tie-break mode.
- `void mode1TBP2Games()`: Updates the games for player 2 in tie-break mode.
- `void mode1SetTBP2Games()`: Updates the games for player 2 in set tie-break mode.

#### Private Methods

- `_resetGame()`: Resets the game state.

#### Private Members

- `IPlayer* _player1`: Pointer to player 1 object.
- `IPlayer* _player2`: Pointer to player 2 object.
- `GameState* _gameState`: Pointer to the game state object.
- `History* _history`: Pointer to the history object.
- `Mode1TieBreaker _mode1TieBreaker`: Instance of the `Mode1TieBreaker` class.
- `PointLeds _pointLeds`: Instance of the `PointLeds` class.
- `GameLeds _gameLeds`: Instance of the `GameLeds` class.
- `SetLeds _setLeds`: Instance of the `SetLeds` class.
- `WinSequences _mode1WinSequences`: Instance of the `WinSequences` class.
- `Undo _undo`: Instance of the `Undo` class.
- `ScoreBoard* _scoreBoard`: Pointer to the score board object.

# Mode1Score.h

This file contains the declaration of the `Mode1Score` class.

## Class Definition

### `Mode1Score`

#### Constructors

- `Mode1Score(IPlayer* player1, IPlayer* player2, PinInterface* pinInterface, GameState* gameState, History* history)`: Constructs a `Mode1Score` object with the given player objects, pin interface, game state, and history.

#### Destructor

- `~Mode1Score()`: Destructs the `Mode1Score` object.

#### Public Methods

- `void setScoreBoard(ScoreBoard* scoreBoard)`: Sets the score board for the `Mode1Score` object.
- `void updateScore(IPlayer* currentPlayer)`: Updates the score for the current player.
- `void mode1P1Score()`: Updates the score for player 1.
- `void mode1P2Score()`: Updates the score for player 2.
- `void mode1P1Games()`: Updates the games for player 1.
- `void mode1P2Games()`: Updates the games for player 2.
- `void mode1TBP1Games()`: Updates the games for player 1 in tie-break mode.
- `void mode1SetTBP1Games()`: Updates the games for player 1 in set tie-break mode.
- `void mode1TBP2Games()`: Updates the games for player 2 in tie-break mode.
- `void mode1SetTBP2Games()`: Updates the games for player 2 in set tie-break mode.

#### Private Methods

- `_resetGame()`: Resets the game state.

#### Private Members

- `IPlayer* _player1`: Pointer to player 1 object.
- `IPlayer* _player2`: Pointer to player 2 object.
- `GameState* _gameState`: Pointer to the game state object.
- `History* _history`: Pointer to the history object.
- `Mode1TieBreaker _mode1TieBreaker`: Instance of the `Mode1TieBreaker` class.
- `PointLeds _pointLeds`: Instance of the `PointLeds` class.
- `GameLeds _gameLeds`: Instance of the `GameLeds` class.
- `SetLeds _setLeds`: Instance of the `SetLeds` class.
- `WinSequences _mode1WinSequences`: Instance of the `WinSequences` class.
- `Undo _undo`: Instance of the `Undo` class.
- `ScoreBoard* _scoreBoard`: Pointer to the score board object.

# Mode1ScoreTest.cpp

This file contains the unit tests for the `Mode1Score` class.

## Test Fixture

### `Mode1ScoreTest`

#### Protected Members

- `MockPlayer player1`: Mock object of the `Player` class representing player 1.
- `MockPlayer player2`: Mock object of the `Player` class representing player 2.
- `MockPinInterface pinInterface`: Mock object of the `PinInterface` class.
- `MockGameState gameState`: Mock object of the `GameState` class.
- `MockHistory history`: Mock object of the `History` class.
- `Mode1Score* mode1Score`: Pointer to the `Mode1Score` object being tested.

#### Test Methods

- `void SetUp()`: Set up the test fixture.
- `void TearDown()`: Tear down the test fixture.

## Test Cases

### `Mode1P1ScoreTest`

#### Test Method

- `TEST(Mode1ScoreTest, Mode1P1ScoreTest)`

#### Description

This test case verifies that the `mode1P1Score` method correctly updates the score for player 1.

### `TestMode1P1Score_LessThan3Points`

#### Test Method

- `TEST_F(Mode1ScoreTest, TestMode1P1Score_LessThan3Points)`

#### Description

This test case verifies that the `mode1P1Score` method does not update the score if the current player has less than 3 points.

### `TestMode1P1Score_3Points_LessThan3PointsP2`

#### Test Method

- `TEST_F(Mode1ScoreTest, TestMode1P1Score_3Points_LessThan3PointsP2)`

#### Description

This test case verifies that the `mode1P1Score` method updates the score for player 1 and player 2 if both players have 3 points.

### `TestMode1P1Score_3Points_EqualPoints`

#### Test Method

- `TEST_F(Mode1ScoreTest, TestMode1P1Score_3Points_EqualPoints)`

#### Description

This test case verifies that the `mode1P1Score` method updates the score for player 1 and player 2 if both players have 3 points.

### `TestMode1P1Score_MoreThan3Points_DifferenceMoreThan1`

#### Test Method

- `TEST_F(Mode1ScoreTest, TestMode1P1Score_MoreThan3Points_DifferenceMoreThan1)`

#### Description

This test case verifies that the `mode1P1Score` method updates the score for player 1 and increments the games if player 1 has more than 3 points and the difference between player 1's points and player 2's points is more than 1.

### `TestMode1P1Score_4Points`

#### Test Method

- `TEST_F(Mode1ScoreTest, TestMode1P1Score_4Points)`

#### Description

This test case verifies that the `mode1P1Score` method updates the score for player 1 and sets the point flash and toggle if player 1 has 4 points.

These are the main files and their contents that make up the program.