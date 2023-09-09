# Your Roles
	- Expert C++ Developer
	- My excellent teacher
	- My helpful assistant

# Your Task
	- Create a unit test for the memory() method.
    - Make sure to cover all test cases.
    - Do not abreviate any code.
    - Write your output to a downloadable c++ file.
    - Use the following source code to help you understand how it works:

```cpp
#ifndef Undo_h
#define Undo_h
#include "../Arduino/Arduino.h"
#include "../GameLeds/GameLeds.h"
#include "../GameState/GameState.h"
#include "../GameTimer/GameTimer.h"
#include "../History/History.h"
#include "../Logger/Logger.h"
#include "../PointLeds/PointLeds.h"
#include "../PinInterface/PinInterface.h"
#include "../ServeLeds/ServeLeds.h"
#include "../SetLeds/SetLeds.h"
#include "../TieLeds/TieLeds.h"
#include "../TennisConstants/TennisConstants.h"

class Undo {
    
 public:
    Undo( 
        Player*         player1, 
        Player*         player2, 
        PinInterface*   pinInterface, 
        GameState*      gameState );

    ~Undo();
    void setMode1Undo( History* history );
    void memory();
    void mode1Undo( History* history );
    void setScoreBoard( ScoreBoard* scoreBoard );

 private:
    Player*       _player1; std::map< std::string, int > _player1_set_history;
    Player*       _player2; std::map< std::string, int > _player2_set_history;
    bool          _scoreBoardSet;
    PinInterface* _pinInterface;
    GameState*    _gameState;
    PointLeds     _pointLeds;
    GameLeds      _gameLeds;
    SetLeds       _setLeds;
    ServeLeds     _serveLeds;
    TieLeds       _tieLeds;
    Logger*       _logger; };
#endif

#include "Undo.h"

Undo::Undo( Player* player1, Player* player2, PinInterface* pinInterface, GameState* gameState ): 
    _player1( player1 ), _player2( player2 ),
    _gameState( gameState ),
    _pointLeds( player1, player2, pinInterface ),
    _gameLeds( player1, player2, pinInterface ),
    _setLeds( player1, player2, pinInterface ),
    _serveLeds( pinInterface, gameState ),
    _tieLeds( pinInterface ) {
        _logger = new Logger( "Undo" ); 
        _scoreBoardSet = false; };
Undo::~Undo(){
    std::cout << "*** Undo destructor called. ***" << std::endl;
    delete _logger; };

void Undo::setScoreBoard( ScoreBoard* scoreBoard ) {
    _pointLeds.setScoreBoard(          scoreBoard ); 
    _gameLeds.setScoreBoard(           scoreBoard ); 
    _setLeds.setScoreBoard(            scoreBoard );
    _scoreBoardSet = true;
}

void Undo::memory() {
    _gameState->setP1PointsMem(       _player1->getPoints()); _gameState->setP2PointsMem( _player2->getPoints());
    _gameState->setP1GamesMem(        _player1->getGames());  _gameState->setP2GamesMem(  _player2->getGames());
    _gameState->setP1SetsMem(         _player1->getSets());   _gameState->setP2SetsMem(   _player2->getSets());
    _gameState->setTieBreakMem(       _gameState->getTieBreak());
    _gameState->setSetTieBreakMem(    _gameState->getSetTieBreak());
    _gameState->setPlayer1SetHistory( _player1->getSetHistory());
    _gameState->setPlayer2SetHistory( _player2->getSetHistory()); }

void Undo::setMode1Undo( History* history ) {
    GameState gameState;
    gameState.setPlayer1Points( _player1->getPoints()); gameState.setP1PointsMem( _gameState->getP1PointsMem());
    gameState.setPlayer2Points( _player2->getPoints()); gameState.setP2PointsMem( _gameState->getP2PointsMem());
    gameState.setPlayer1Games( _player1->getGames());  gameState.setP1GamesMem( _gameState->getP1GamesMem());
    gameState.setPlayer2Games( _player2->getGames()); gameState.setP2GamesMem( _gameState->getP2GamesMem());
    gameState.setPlayer1Sets( _player1->getSets()); gameState.setP1SetsMem( _gameState->getP1SetsMem());
    gameState.setPlayer2Sets( _player2->getSets()); gameState.setP2SetsMem( _gameState->getP2SetsMem());
    gameState.setPlayer1Matches( _player1->getMatches()); gameState.setPlayer2Matches( _player2->getMatches());
    gameState.setServe( _gameState->getServe());
    gameState.setServeSwitch( _gameState->getServeSwitch());
    gameState.setUndo( _gameState->getUndo());
    gameState.setStarted( _gameState->getStarted());
    gameState.setPointFlash( _gameState->getPointFlash());
    gameState.setRotaryPosition( _gameState->getRotaryPosition());
    gameState.setPrevRotaryPosition( _gameState->getPrevRotaryPosition());
    gameState.setRotaryChange( _gameState->getRotaryChange());
    gameState.setToggle( _gameState->getToggle());
    gameState.setTieLEDsOn( _gameState->getTieLEDsOn());
    gameState.setTieBreak( _gameState->getTieBreak());
    gameState.setSetTieBreak( _gameState->getSetTieBreak());
    gameState.setSetTieBreakMem( _gameState->getSetTieBreakMem());
    gameState.setTieBreakOnly( _gameState->getTieBreakOnly());
    gameState.setTieBreakMem( _gameState->getTieBreakMem());
    gameState.setPlayer1SetHistory( _player1->getSetHistory());
    gameState.setPlayer2SetHistory( _player2->getSetHistory());
    _gameState->setPlayer1SetHistory( _player1->getSetHistory());
    _gameState->setPlayer2SetHistory( _player2->getSetHistory());
    history->push( gameState ); }

void Undo::mode1Undo( History* history ) {
    GameTimer::gameDelay( 100 );
    if ( history->size() == 0 ) { return; }
    if ( _scoreBoardSet == false ) { std::cout << "*** ERROR: trying to call undo when _scoreBoardSet == false exiting process... *** " << std::endl; exit( 1 ); }
    GameState gameState = ( history->pop());
    _player1->setPoints( gameState.getPlayer1Points());
    _gameState->setP1PointsMem( gameState.getP1PointsMem());
    _player2->setPoints( gameState.getPlayer2Points());
    _gameState->setP2PointsMem( gameState.getP2PointsMem());
    _player1->setGames( gameState.getPlayer1Games());
    _gameState->setP1GamesMem( gameState.getP1GamesMem());
    _player2->setGames( gameState.getPlayer2Games());
    _gameState->setP2GamesMem( gameState.getP2GamesMem());
    _player1->setSets( &gameState, gameState.getPlayer1Sets());
    _gameState->setP1SetsMem( gameState.getP1SetsMem());
    _player2->setSets( &gameState, gameState.getPlayer2Sets());
    _gameState->setP2SetsMem( gameState.getP2SetsMem());
    _player1->setMatches( gameState.getPlayer1Matches());
    _player2->setMatches( gameState.getPlayer2Matches());
    _gameState->setServe( gameState.getServe());
    _gameState->setServeSwitch( gameState.getServeSwitch());
    _gameState->setUndo( gameState.getUndo());
    _gameState->setStarted( gameState.getStarted());
    _gameState->setPointFlash( gameState.getPointFlash());
    _gameState->setRotaryPosition( gameState.getRotaryPosition());
    _gameState->setPrevRotaryPosition( gameState.getPrevRotaryPosition());
    _gameState->setRotaryChange( gameState.getRotaryChange());
    _gameState->setToggle( gameState.getToggle());
    _gameState->setTieLEDsOn( gameState.getTieLEDsOn());
    _gameState->setTieBreak( gameState.getTieBreak());
    _gameState->setSetTieBreak( gameState.getSetTieBreak());
    _gameState->setSetTieBreakMem( gameState.getSetTieBreakMem());
    _gameState->setTieBreakOnly( gameState.getTieBreakOnly());
    _gameState->setTieBreakMem( gameState.getTieBreakMem());
    if ( _gameState->getTieLEDsOn() == 1 ) { _gameState->setTieLEDsOn( 1 );  _tieLeds.turnOn(); }
    if ( _gameState->getTieLEDsOn() == 0 ) {  _tieLeds.turnOff(); _gameState->setTieLEDsOn( 0 );  } 
    _logger->logUpdate( "updating leds...", __FUNCTION__ );
    _pointLeds.updatePoints();
    _gameLeds.updateGames();
    _setLeds.updateSets();
    _serveLeds.updateServeLED();
}
```
    - Use the following source code as a template for your unit test:
```cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Mode1Score.h"
#include "../History/History.h"
#include "../Player/Player.h"

class Mode1ScoreTest : public ::testing::Test {
protected:
    PinInterface* inInterface; 
    History* history;
    Mode1Score* mode1Score;
    ScoreBoard* scoreBoard;
    Player* player1;
    Player* player2;
    GameState* gameState;
    PinInterface* pinInterface;
    PinState* pinState;
    std::map< std::string, int > pin_map;

    void SetUp() override {
        gameState = new GameState();
        player1 = new Player( gameState, PLAYER_1_INITIALIZED );
        player2 = new Player( gameState, PLAYER_2_INITIALIZED ); 
        player1->setOpponent( player2 ); player2->setOpponent( player1 );
        history = new History();
        pin_map = {{ "pin", 0 }};
        pinState = new PinState( pin_map );
        pinInterface = new PinInterface( pinState );
        mode1Score = new Mode1Score( player1, player2, pinInterface, gameState, history );
        scoreBoard = new ScoreBoard( player1, player2, gameState );
        mode1Score->setScoreBoard( scoreBoard );
        undoObj = new Undo( player1, player2, pinInterface, gameState );
        undoObj->setScoreBoard( new ScoreBoard( player1, player2, gameState ));
    }

    void TearDown() override {
        delete mode1Score;
        delete scoreBoard;
        delete player1;
        delete player2;
        delete gameState;
        delete history; 
        delete pinInterface;
        delete pinState; 
        std::cout << "\n\n" << std::endl;
        }
};

TEST_F( Mode1ScoreTest, TestFirstScore ) {   
    std::cout << "make sure player scores are 0" << std::endl;
    ASSERT_EQ( 0, player1->getPoints());
    ASSERT_EQ( 0, player2->getPoints());

    std::cout << "increment player 1 score" << std::endl;
    player1->setPoints( 1 );

    mode1Score->updateScore( player1 );

    ASSERT_EQ( "PLAYER 1: ////// I 15 //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   00 //////", scoreBoard->drawPlayerScore( player2 ));
}


TEST_F( Mode1ScoreTest, TestPlayerPointsEqualOpponentPoints) {
    std::cout << "TestPlayerPointsEqualOpponentPoints..." << std::endl;
    player1->setPoints( 3 );
    player2->setPoints( 3 );
    mode1Score->updateScore( player1 );                                          
    ASSERT_EQ( 3, player1->getPoints());
    ASSERT_EQ( 3, player2->getPoints());           
    std::cout << " finished TestPlayerPointsEqualOpponentPoints." << std::endl;
}

TEST_F( Mode1ScoreTest, TestPlayerWinsGame ) {
    player1->setPoints( 5 );
    player2->setPoints( 3 );
    mode1Score->updateScore( player1 );    
    ASSERT_EQ( 1, player1->getGames());     // player 1 wins game    
    ASSERT_EQ( 0, player2->getGames()); }

TEST_F( Mode1ScoreTest, TestMode1P1Score_3Points) {
    player1->setPoints( 3 );                        // Arrange
    player2->setPoints( 2 );   
    mode1Score->updateScore( player1 );             // Act
    EXPECT_EQ( player1->getPoints(), 3);
    EXPECT_EQ( player2->getPoints(), 2 );            // Assert
    ASSERT_EQ( "PLAYER 1: ////// I 40 //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   30 //////", scoreBoard->drawPlayerScore( player2 ));
}
```