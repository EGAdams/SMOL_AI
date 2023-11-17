# Your role
- World-class C++ developer
- World-class Object-Oriented Design (OOD) software architect
- Adhere to the SOLID principles of software design
- Adhere to the DRY principle of software design
- Seasoned user of the Gang of Four (GoF) design patterns

# Your task
- Please make a list of objects that you would need to create this product. For each object, please list the attributes and methods you need to implement. Please also list the data types of each attribute and the return type of each method.
- Use the Product Requirements Document (PRD) below as a guide.

# Tennis Scoreboard Product Requirements Document (PRD)
## Introduction

This document outlines the requirements for a digital tennis scoreboard. The scoreboard is designed to enhance the user experience during tennis matches by providing clear and accurate scorekeeping, including tie-break situations, with the use of a remote control for player input.

## Product Overview

The scoreboard is a digital display system used in tennis matches to show current scores, set histories, and serving turns. It replicates the appearance of a HUB75 LED panel, employs SVG for clarity, and incorporates features specific to tie-break scenarios.

## Product Features

- **Score Display**: Utilizes large SVG numerals for player points and smaller figures for game counts, set scores, and set histories.
- **Tie-Breaker Display**: Incorporates a blue bar to signify the onset of a tie-break.
- **Server Indicator**: Highlights which player is due to serve next.
- **Remote Control**: Players interact with the scoreboard using a remote furnished with 'Score', 'Undo', and 'Reset Game' buttons.

## Product Components and Responsibilities

1. **GameModel**
   - Manages the match state, including scores, server, and history.
2. **PlayerScore**
   - Handles the scoring logic for each player, storing game, set, and tie-break scores.
3. **TieBreaker**
   - Manages the logic and scoring during tie-breaks.
4. **RemoteControl**
   - Allows players to input score changes, undo actions, and reset the game.
5. **Scoreboard (View)**
   - Displays the scores and match information as updated by the GameModel.
6. **MatchController**
   - Intermediates between the GameModel, Scoreboard, and player input to update the game state.



## Detailed Requirements

### Software Requirements

- **GameModel**:
  - Attributes:
    - `currentServerId` (Integer): Identifier for the player who is currently serving.
    - `matchHistory` (Array): Records past scores and actions for the undo feature.
  - Methods:
    - `updateScore(playerId: Integer, points: Integer)`: Updates the score for the player.
    - `undoLastAction()`: Reverts to the last historical state.
    - `resetMatch()`: Clears scores and resets the match.
    - `recordHistory()`: Saves the current state to history.

- **PlayerScore**:
  - Attributes:
    - `playerId` (Integer): The unique identifier for the player.
    - `gameScore` (Integer): The current score in the game.
    - `setScore` (Array of Integers): List of games won in each set.
    - `tieBreakScore` (Integer): The current score in a tie-break.
  - Methods:
    - `updateGameScore(points: Integer)`: Updates the game score.
    - `updateSetScore(setPoints: Integer)`: Updates the set score.
    - `updateTieBreakScore(points: Integer)`: Updates the tie-break score.
    - `resetScores()`: Resets scores for a new match.

- **TieBreaker**:
  - Attributes:
    - `playerScores` (Array of Integers): Scores for each player during the tie-break.
    - `winningScore` (Integer): The score needed to win the tie-break.
  - Methods:
    - `incrementScore(playerId: Integer)`: Increases the player's score.
    - `isWinningScoreReached(playerId: Integer)`: Checks for a tie-break win condition.
    - `resetTieBreak()`: Resets the tie-break scores.

- **RemoteControl**:
  - Attributes:
    - `assignedPlayerId` (Integer): The ID of the player using the remote.
  - Methods:
    - `score()`: Signals a point increase for the player.
    - `undo()`: Signals an undo action.
    - `reset()`: Signals to reset the match.

- **Scoreboard (View)**:
  - Methods:
    - `displayScore(playerScores: Array of PlayerScore)`: Shows player scores.
    - `displayServerIndicator(currentServerId: Integer)`: Indicates the current server.
    - `displayTieBreakIndicator(isInTieBreak: Boolean)`: Indicates if a tie-break is in progress.
    - `displayMatchHistory(matchHistory: Array)`: Optionally shows the match history.

- **MatchController**:
  - Attributes:
    - `gameModel` (GameModel): The state model of the match.
    - `scoreboard` (Scoreboard): The display component.
  - Methods:
    - `startMatch()`: Initializes the match.
    - `handlePlayerInput(actionType: String, playerId: Integer)`: Processes player inputs from the remote.

### User Requirements

- The system should be able to display the current score for each player.

## Conclusion

This document serves as a roadmap for developing a tennis scoreboard system that enhances player experience through autonomous score updates and clear visual indications, adhering to the principles of focused responsibilities and modular design.

