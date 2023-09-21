Act as a world-class C++ developer, my helpfull assistant, and a my expert teacher.

We are going to examine the folloing C++ file because we need to write unit test for it, ok?

```cpp
#include "Mode1Score.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

Mode1Score::Mode1Score( Player* player1, IPlayer* player2,
    IPinInterface* pinInterface, IGameState* gameState, IHistory* history ) :
    _player1( player1 ),
    _player2( player2 ),
    _gameState( gameState ),
    _history( history ),
    _TieBreaker( player1, player2, pinInterface, gameState, history ),
    _pointLeds( player1, player2, pinInterface ),
    _gameLeds( player1, player2, pinInterface ),
    _setLeds( player1, player2, pinInterface ),
    _mode1WinSequences( player1, player2, pinInterface, gameState ),
    _undo( player1, player2, pinInterface, gameState ) {}
Mode1Score::~Mode1Score() {}

void Mode1Score::setScoreBoard( ScoreBoard* scoreBoard ) { 
    _pointLeds.setScoreBoard(          scoreBoard ); 
    _gameLeds.setScoreBoard(           scoreBoard ); 
    _mode1WinSequences.setScoreBoards( scoreBoard ); 
    _setLeds.setScoreBoard(            scoreBoard ); }

void Mode1Score::_resetGame() {
     GameTimer::gameDelay( UPDATE_DISPLAY_DELAY );
    _player1->setPoints( 0 );
    _player2->setPoints( 0 );
    _gameState->setServeSwitch( 1 );
    _gameState->setServe( 0 );
    _pointLeds.updatePoints(); }

void Mode1Score::updateScore(IPlayer* currentPlayer) {
    // std::cout << "Entering updateScore method..." << std::endl;
    IPlayer* otherPlayer = currentPlayer->getOpponent();
    std::cout << "Current Player Points: " << currentPlayer->getPoints() << std::endl;
    std::cout << "Other Player Points: " << otherPlayer->getPoints() << std::endl;

    if ( currentPlayer->getPoints() >= 3 ) {
        // std::cout << "Player points >= 3" << std::endl;  // Debug
        int delta_score = currentPlayer->getPoints() - otherPlayer->getPoints();
        // std::cout << "delta_score: " << delta_score << std::endl;  // Debug
        if ( currentPlayer->getPoints() == otherPlayer->getPoints()) {
            // std::cout << "Player points == Opponent points" << std::endl;  // Debug
            currentPlayer->setPoints( 3 );
            otherPlayer->setPoints( 3 );
        } else if ( delta_score > 1 ) {
            // std::cout << "current player games: " << currentPlayer->getGames() << std::endl;
            currentPlayer->setGames( currentPlayer->getGames() + 1 );
            // std::cout << "current player games + 1: " << currentPlayer->getGames() << std::endl;
            _undo.memory();
            // std::cout << "current player number: " << currentPlayer->number() << std::endl;
            currentPlayer->number() == 0 ? mode1P1Games() : mode1P2Games();
        }  else if ( currentPlayer->getPoints() == 4) {
            _gameState->setPointFlash( 1 );
            _gameState->setPreviousTime(GameTimer::gameMillis());
            _gameState->setToggle( 0 );
        }
    }
    _pointLeds.updatePoints();
}
```