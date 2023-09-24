# Your Role
- Expert C++ Developer
- My helpful assistant
- A Software Design Pattern GoF Expert
- A Developer who always adheres to the SOLID Principles of Object Oriented Design

# Your Task
- Create a C++ method to conform to the Flowchart below
- Use a Player object passed in as the current player.  Use the Player object's method getOpponent() method to get a pointer to the opponent Player Object.

# The Mermaid Flowchart describing the method you need to create
```mermaid
graph TD

start[Start: TieBreak->run]
scoreboardUpdate[ ScoreBoard Update ]
serveSwitch[_gameState->setServeSwitch]
decision1{ \nTie Break Win Set to 15 Points\nPlayer Points = 15\n\n}
p1TBSetWinSequence1[ \nTie-Breaker Set Win Fireworks\n\n ]
endTieBreak1[endTieBreak]
decision3{ Game Win Scenario:\n\nPlayer Points >= 10 \nLeads Opponent by 2\n}
p1TBSetWinSequence2[ \nTie-Breaker Set Win Fireworks\n\n ]
endTieBreak2[endTieBreak]

start --> scoreboardUpdate
scoreboardUpdate --> serveSwitch
serveSwitch --> decision1
decision1 -- YES --> p1TBSetWinSequence1
decision1 -- NO --> decision3
p1TBSetWinSequence1 --> endTieBreak1
decision3 -- YES --> p1TBSetWinSequence2
decision3 -- NO --> end1
p1TBSetWinSequence2 --> endTieBreak2
endTieBreak2 --> end1

end1[End]
```

# Your Solution
```cpp
class Player {
public:
    int getPoints() const;
    Player* getOpponent() const;
    // ... other methods and members
};

class GameState {
public:
    void setServeSwitch();
    // ... other methods and members
};

class ScoreBoard {
public:
    void update();
    // ... other methods and members
};

class TieBreak {
private:
    GameState* _gameState;
    ScoreBoard _scoreBoard;

    void displayFireworks() {
        // logic to display fireworks
    }

public:
    void run(Player& currentPlayer) {
        _scoreBoard.update();
        _gameState->setServeSwitch();

        if (currentPlayer.getPoints() == 15) {
            displayFireworks();
            // end tiebreak
            return;
        }

        Player* opponent = currentPlayer.getOpponent();
        if (currentPlayer.getPoints() >= 10 && 
            (currentPlayer.getPoints() - opponent->getPoints() >= 2)) {
            displayFireworks();
            // end tiebreak
            return;
        }

        // end the method if neither condition is met
    }
};
```

## link to gpt4 chat session
https://chat.openai.com/share/0f0afbb8-82d8-42c3-bb3c-215332395873

## gpt-3.5 answer
https://chat.openai.com/share/1b6037d3-0c6e-4f2a-a1c6-5039338808b8
