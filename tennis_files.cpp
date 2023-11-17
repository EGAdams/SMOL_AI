#include "Inputs.h"
#include "../Arduino/Arduino.h"
#include "../TennisConstants/TennisConstants.h"
#include <string>
#include <iostream>

Inputs::Inputs( Player* player1,
    Player* player2,
    PinInterface* pinInterface,
    GameState* gameState )
    : _player1( player1 ),
    _player2( player2 ),
    _pinInterface( pinInterface ),
    _gameState( gameState ),
    _reset( player1, player2, pinInterface, gameState ) {
    _logger = new Logger( "Inputs" ); }
Inputs::~Inputs() {
    std::cout << "*** Inputs destructor called. ***" << std::endl;
    delete _logger; }

void Inputs::readReset() {
    if ( _pinInterface->pinDigitalRead( RESET ) == LOW ) {
        if ( SIMULATION == 0 ) { while ( _pinInterface->pinDigitalRead( RESET ) == LOW ) { GameTimer::gameDelay( 25 ); }}  // Wait for the button to be released
        _reset.resetScoreboard(); }}

void Inputs::readUndoButton() {
    return; // DISABLED
    if ( _pinInterface->pinDigitalRead( UNDO ) == LOW ) {
        if ( SIMULATION == 0 ) { 
            while ( _pinInterface->pinDigitalRead( UNDO ) == LOW ) { 
                GameTimer::gameDelay( 25 ); 
            }
        } // Wait for the button to be released
        _gameState->setUndo( 1 ); 
    }
}

int Inputs::readRotary() {  // TODO: make this one read.
    _gameState->setRotaryPosition( 0 );  // int rotaryPosition = 0;
    int rotaryAnalogValue = _pinInterface->pinAnalogRead( ROTARY );
    #if defined _WIN32 || defined _WIN64
        std::cout << "rotary analog value: " << rotaryAnalogValue << std::endl;
    #endif
    if ( rotaryAnalogValue <= 100 ) { _gameState->setRotaryPosition( 1 ); }
    if ( rotaryAnalogValue >= 350 && rotaryAnalogValue <= 450 ) { _gameState->setRotaryPosition( 2 ); }
    if ( rotaryAnalogValue >= 550 && rotaryAnalogValue <= 700 ) { _gameState->setRotaryPosition( 3 ); }
    if ( rotaryAnalogValue >= 750 && rotaryAnalogValue <= 800 ) { _gameState->setRotaryPosition( 4 ); }
    if ( rotaryAnalogValue >= 850 && rotaryAnalogValue <= 1000 ) { _gameState->setRotaryPosition( 5 ); }
    if ( _gameState->getRotaryPosition() != _gameState->getPrevRotaryPosition() ) {
        _gameState->setRotaryChange( 1 );
        _gameState->setPrevRotaryPosition( _gameState->getRotaryPosition() );
        _reset.refresh();  // set rotaryChange to false and reset the scoreboard
    }
    return _gameState->getRotaryPosition(); }

void Inputs::readPlayerButtons() {
    return; // DISABLED
    int anlgPlyrBtnVal = _pinInterface->pinAnalogRead( PLAYER_BUTTONS );
    std::cout << "\n\n\n\n\nplayer button read: " << anlgPlyrBtnVal << std::endl;
    if ( anlgPlyrBtnVal <= 1000 ) {  // if one of the player buttons is pressed...
        GameTimer::gameDelay( 20 );
        if ( anlgPlyrBtnVal <= 50 ) {                                _gameState->setPlayerButton( 1 ); }
        else if ( anlgPlyrBtnVal >= 350 && anlgPlyrBtnVal <= 400 ) { _gameState->setPlayerButton( 2 ); }
        else if ( anlgPlyrBtnVal >= 550 && anlgPlyrBtnVal <= 650 ) { _gameState->setPlayerButton( 3 ); }
        else if ( anlgPlyrBtnVal >= 750 && anlgPlyrBtnVal <= 800 ) { _gameState->setPlayerButton( 4 ); }
        #if defined _WIN32 || defined _WIN64
            std::cout << "player button: " << _gameState->getPlayerButton() << std::endl;
            // _logger->logUpdate( "set player button to [" + std::to_string( _gameState->getPlayerButton()) + "]" , __FUNCTION__ );
        #else
            while ( _pinInterface->pinAnalogRead( PLAYER_BUTTONS ) <= 1000 ) { GameTimer::gameDelay( 20 ); }
        #endif
    }}
#ifndef Inputs_h
#define Inputs_h

#include "../Arduino/Arduino.h"
#include "../GameState/GameState.h"
#include "../GameTimer/GameTimer.h"
#include "../PinInterface/PinInterface.h"
#include "../Inputs/Inputs.h"
#include "../Logger/Logger.h"
#include "../Reset/Reset.h"

class Inputs {
 public:
  Inputs( Player* player1,
          Player* player2,
         PinInterface* pinInterface,
         GameState* gameState);
  ~Inputs();
  void readReset();
  void readUndoButton();
  int readRotary();
  void readPlayerButtons();

 private:
  Player* _player1;
  Player* _player2;
  PinInterface* _pinInterface;
  GameState* _gameState;
  Reset _reset;
  Logger* _logger;
};

#endif
#ifndef MODE_1_WIN_SEQUENCES_H
#define MODE_1_WIN_SEQUENCES_H

#include "../Arduino/Arduino.h"
#include "../TennisConstants/TennisConstants.h"
#include "../GameLeds/GameLeds.h"
#include "../GameState/GameState.h"
#include "../GameTimer/GameTimer.h"
#include "../GameWinSequence/GameWinSequence.h"
#include "../PointLeds/PointLeds.h"
#include "../PinInterface/PinInterface.h"
#include "../Player/Player.h"
#include "../Reset/Reset.h"
#include "../SetLeds/SetLeds.h"
#include "../MatchWinSequence/MatchWinSequence.h"
#include "../Undo/Undo.h"
#include "../ScoreBoard/ScoreBoard.h"
#include "../SetWin/SetWin.h"

class Mode1WinSequences {
 public:
    Mode1WinSequences(  Player* player1,
                        Player* player2,
                        PinInterface* pinInterface,
                        GameState* gameState);
    ~Mode1WinSequences();
    void setScoreBoards( ScoreBoard* scoreBoard );
    void p1GameWinSequence();
    void p1SetWinSequence();
    void playerOneMatchWin();
    void p2GameWinSequence();
    void p2SetWinSequence();
    void playerTwoMatchWin();
    void p1TBGameWinSequence();
    void p2TBGameWinSequence();
    void p1TBSetWinSequence();
    void p2TBSetWinSequence();
    void p1SetTBWinSequence();
    void p2SetTBWinSequence();
    void p1TBMatchWinSequence();
    void p2TBMatchWinSequence();
    void tieLEDsOn();
    void tieLEDsOff();

 private:
    Player* _player1;
    Player* _player2;
    PinInterface* _pinInterface;
    GameState* _gameState;
    PointLeds _pointLeds;
    GameLeds _gameLeds;
    SetLeds _setLeds;
    Reset _reset;
    Undo _undo;
    SetWin* _setWin;
    ScoreBoard* _scoreBoard; };
#endif#include "WinSequences.h"

Mode1WinSequences::~Mode1WinSequences() {
    // std::cout << "*** Mode1WinSequences destructor called. ***" << std::endl;
    delete _setWin; }

Mode1WinSequences::Mode1WinSequences( Player* player1, Player* player2, PinInterface* pinInterface,
                                      GameState* gameState ):
    _player1( player1 ), _player2( player2 ),
    _pinInterface( pinInterface ),
    _gameState( gameState ),
    _pointLeds( player1, player2, pinInterface ),
    _gameLeds( player1, player2, pinInterface ),
    _setLeds( player1, player2, pinInterface ),
    _reset( player1, player2, pinInterface, gameState ),
    _undo( player1, player2, pinInterface, gameState ) {
        _setWin = new SetWin( &_undo, _gameState, &_setLeds );}

void Mode1WinSequences::setScoreBoards( ScoreBoard* scoreBoard ) {
    _pointLeds.setScoreBoard( scoreBoard );
    _gameLeds.setScoreBoard(  scoreBoard );
    _setLeds.setScoreBoard(   scoreBoard );
    _scoreBoard =             scoreBoard; } // set mine too!

void Mode1WinSequences::p1GameWinSequence() {
    std::cout << "//////////////////////// p1GameWinSequence() ////////////////////////" << std::endl;
    GameWinSequence gameWinSequence;
    gameWinSequence.run( _player1, _gameState, &_gameLeds, _scoreBoard, _player1->getGames());
    std::cout << "*** inside WinSequences class.  p1GameWinSequence() ***" << std::endl;
    _undo.memory();
    std::cout << "*** delaying game after p1GameWinSequence()... ***" << std::endl;
    GameTimer::gameDelay( GAME_FLASH_DELAY );
    std::cout << "*** done delaying game after p1GameWinSequence()  setting points to zero... ***" << std::endl;
    _player1->setPoints( 0 );
    _player2->setPoints( 0 );
    _gameState->setPlayer1Points( 0 );
    _gameState->setPlayer2Points( 0 );  }

void Mode1WinSequences::p1SetWinSequence() {
    std::cout << "*** executing _setWin->execute for player one... ***" << std::endl;
    _setWin->execute( _player1, _scoreBoard ); }

void Mode1WinSequences::playerOneMatchWin() {
    std::cout << "//////////////////////// playerOneMatchWin() ////////////////////////" << std::endl;
    _undo.memory();
    _pointLeds.updateTBPoints();
    MatchWinSequence matchWinSequence; matchWinSequence.run( _player1, _gameState, &_gameLeds, &_setLeds );
    _reset.resetScoreboard(); }

void Mode1WinSequences::playerTwoMatchWin() {
    std::cout << "//////////////////////// playerTwoMatchWin() ////////////////////////" << std::endl;
    _undo.memory();
    _pointLeds.updateTBPoints();
    MatchWinSequence matchWinSequence; matchWinSequence.run( _player2, _gameState, &_gameLeds, &_setLeds );
    _reset.resetScoreboard(); }


void Mode1WinSequences::p2GameWinSequence() {
    GameWinSequence gameWinSequence;
    gameWinSequence.run( _player2, _gameState, &_gameLeds, _scoreBoard, _player2->getGames());
    std::cout << "*** inside WinSequences class.  executing p2GameWinSequence()... ***" << std::endl;
    _undo.memory();
    std::cout << "*** delaying game after p2GameWinSequence()... ***" << std::endl;
    GameTimer::gameDelay( GAME_FLASH_DELAY );
    std::cout << "*** done delaying game after p2GameWinSequence()  setting points to zero... ***" << std::endl;
    _player1->setPoints( 0 );
    _player2->setPoints( 0 );
    _gameState->setPlayer1Points( 0 );
    _gameState->setPlayer2Points( 0 ); }

void Mode1WinSequences::p2SetWinSequence() {
     std::cout << "*** executing _setWin->execute... ***" << std::endl;
    _setWin->execute( _player2, _scoreBoard ); }



void Mode1WinSequences::p1TBGameWinSequence() {
    _undo.memory();
    if ( _scoreBoard->hasCanvas()) {
        GameWinSequence gameWinSequence;
        gameWinSequence.run( _player1, _gameState, &_gameLeds, _scoreBoard, _player1->getGames());
    } else {
        for ( int currentPulseCount = 0; currentPulseCount < _gameState->getGameWinPulseCount();
                currentPulseCount++ ) {
                _player1->setSets( _gameState, 0 );
                _setLeds.updateSets();
                GameTimer::gameDelay( _gameState->getFlashDelay());
                _player1->setSets(    _gameState, _gameState->getP1SetsMem());
                _setLeds.updateSets();
                GameTimer::gameDelay( _gameState->getFlashDelay());}}
    tieLEDsOff();
    _gameState->setTieBreak( 0 );
    _player1->setGames( 0 );
    _player2->setGames( 0 );
    _gameLeds.updateGames();}

void Mode1WinSequences::p2TBGameWinSequence() {
    _undo.memory();
    if ( _scoreBoard->hasCanvas()) {     // the matrix is active
        GameWinSequence gameWinSequence;
        gameWinSequence.run( _player2, _gameState, &_gameLeds, _scoreBoard, _player2->getGames());
    } else {
        for ( int currentPulseCount = 0;
            currentPulseCount < _gameState->getGameWinPulseCount();
            currentPulseCount++ ) {
            _player2->setSets( _gameState, 0 );
            _setLeds.updateSets();
            GameTimer::gameDelay( _gameState->getFlashDelay());
            _player2->setSets( _gameState, _gameState->getP2SetsMem());
            _setLeds.updateSets();
            GameTimer::gameDelay( _gameState->getFlashDelay()); }}
    tieLEDsOff();
    _gameState->setTieBreak( 0 );
    _player1->setGames( 0 );
    _player2->setGames( 0 );
    _gameLeds.updateGames(); }


////////////////////////////////// SET WIN SEQUENCES //////////////////////////////////////////////
void Mode1WinSequences::p1TBSetWinSequence() {  // for entering set t/b
    _undo.memory();
    for ( int currentPulseCount = 0; currentPulseCount < SET_WIN_PULSE_COUNT; currentPulseCount++ ) {
        _player1->setSets( _gameState, 0 );
        tieLEDsOff();
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());
        _player1->setSets( _gameState, 1 );
        tieLEDsOn();
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());}
    _player1->setGames( 0 );
    _player2->setGames( 0 );
    tieLEDsOn();}

void Mode1WinSequences::p2TBSetWinSequence() {  // for entering set t/b
    _undo.memory();
    for ( int currentPulseCount = 0; currentPulseCount < SET_WIN_PULSE_COUNT; currentPulseCount++ ) {
        _player2->setSets( _gameState, 0 );
        tieLEDsOff();
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());
        _player2->setSets( _gameState, 1 );
        tieLEDsOn();
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());}
    _player1->setGames( 0 );
    _player2->setGames( 0 );
    tieLEDsOn();}
///////////////////////////// END OF SET WIN SEQUENCES ////////////////////////////////////////////


////////////////////////// SET TIE BREAKER WIN SEQUENCES //////////////////////////////////////////
void Mode1WinSequences::p1SetTBWinSequence() {  // for winning set t/b
    _undo.memory();

    for ( int currentPulseCount = 0; currentPulseCount < SET_WIN_PULSE_COUNT; currentPulseCount++ ) {
        _player1->setSets( _gameState, 0 );
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());
        _player1->setSets( _gameState, 3 );
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());}}

void Mode1WinSequences::p2SetTBWinSequence() {  // for winning set t/b
    _undo.memory();
    for ( int currentPulseCount = 0; currentPulseCount < SET_WIN_PULSE_COUNT; currentPulseCount++ ) {
        _player2->setSets( _gameState, 0 );
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());
        _player2->setSets( _gameState, 3 );
        _setLeds.updateSets();
        GameTimer::gameDelay( _gameState->getFlashDelay());}}
//////////////////////// END OF SET TIE BREAKER WIN SEQUENCES /////////////////////////////////////

void Mode1WinSequences::p1TBMatchWinSequence() {
    _player2->setGames( 99 );
    _gameLeds.updateGames();
    _undo.memory();
    tieLEDsOff();
    MatchWinSequence matchWinSequence; matchWinSequence.run( _player1, _gameState, &_gameLeds, &_setLeds );
    _reset.resetScoreboard();}

void Mode1WinSequences::p2TBMatchWinSequence() {
    _player1->setGames( 99 );
    _gameLeds.updateGames();
    _undo.memory();
    tieLEDsOff();
    MatchWinSequence matchWinSequence; matchWinSequence.run( _player2, _gameState, &_gameLeds, &_setLeds );
    _reset.resetScoreboard();}

void Mode1WinSequences::tieLEDsOn() {
    _gameState->setTieLEDsOn( 1 );  // tieLEDsOn = true;
    _pinInterface->pinDigitalWrite( P1_TIEBREAKER, HIGH );
    _pinInterface->pinDigitalWrite( P2_TIEBREAKER, HIGH );}

void Mode1WinSequences::tieLEDsOff() {
    _gameState->setTieLEDsOn( 0 );  // tieLEDsOn = false;
    _pinInterface->pinDigitalWrite( P1_TIEBREAKER, LOW );
    _pinInterface->pinDigitalWrite( P2_TIEBREAKER, LOW );}
#include "TieBreaker.h"

TieBreaker::TieBreaker( Player* player1,
    Player* player2,
    PinInterface* pinInterface,
    GameState* gameState,
    History* history )
    : _player1( player1 ),
    _player2( player2 ),
    _pinInterface( pinInterface ),
    _gameState( gameState ),
    _history( history ),
    _pointLeds( player1, player2, pinInterface ),
    _gameLeds( player1, player2, pinInterface ),
    _serveLeds( pinInterface, gameState ),
    _setLeds( player1, player2, pinInterface ),
    _mode1WinSequences( player1, player2, pinInterface, gameState ),
    _undo( player1, player2, pinInterface, gameState ) {}

TieBreaker::~TieBreaker() {}

int TieBreaker::_getServe() {
    switch ( _iteration ) {
    case 1:
        return PLAYER_2_SERVE; // doesn't matter who scores here.  doesn't concern me.
        break;
    
    case 2:
        return PLAYER_2_SERVE;
        break;

    case 3:
        return PLAYER_1_SERVE;
        break;

    case 4:
        return PLAYER_1_SERVE;
        break;
    
    case 5:
        return PLAYER_2_SERVE;
        break;
    
    case 6:
        return PLAYER_2_SERVE;
        break;
    
    case 7:
        return PLAYER_1_SERVE;
        break;

    case 8:
        return PLAYER_1_SERVE;
        break;

    case 9:
        return PLAYER_2_SERVE;
        break;

    case 10:
        return PLAYER_2_SERVE;
        break;
    
    case 11:
        return PLAYER_1_SERVE;
        break;

    case 12:
        return PLAYER_1_SERVE;
        break;
    
    case 13:
        return PLAYER_2_SERVE;
        break;

    case 14:
        return PLAYER_2_SERVE;
        break;

    case 15:
        return PLAYER_1_SERVE;
        break;
    
    case 16:
        return PLAYER_1_SERVE;
        break;

    case 17:
        return PLAYER_2_SERVE;
        break;

    case 18:
        return PLAYER_2_SERVE;
        break;

    case 19:
        return PLAYER_1_SERVE;
        break;

    case 20:
        return PLAYER_1_SERVE;
        break;

    case 21:
        return PLAYER_2_SERVE;
        break;

    case 22:
        return PLAYER_2_SERVE;
        break;

    case 23:
        return PLAYER_1_SERVE;
        break;

    case 24:
        return PLAYER_1_SERVE;
        break;

    case 25:
        return PLAYER_2_SERVE;
        break;
    
    default:
        std::cout << "*** WARNING: _getServe() in TieBreaker.cpp is returning default value. ***"
                  << std::endl;
        std::cout << "The iteration is: " << _iteration << std::endl;
        return PLAYER_1_SERVE;
        break;
    }
}

void TieBreaker::setIteration( int iteration ) { _iteration = iteration; }
int  TieBreaker::getIteration() { return _iteration; }
void TieBreaker::incrementIteration() { 
    // std::cout << "Incrementing iteration in TieBreaker::incrementIteration()... " << std::endl;
    _iteration++; }

void TieBreaker::setScoreBoards( ScoreBoard* scoreBoard ) {
    _pointLeds.setScoreBoard( scoreBoard );
    _setLeds.setScoreBoard(   scoreBoard ); 
    _gameLeds.setScoreBoard(  scoreBoard ); 
    _undo.setScoreBoard(      scoreBoard ); 
    _scoreBoard =             scoreBoard; 
}

void TieBreaker::tieLEDsOn() {
    _gameState->setTieLEDsOn( 1 );
    _pinInterface->pinDigitalWrite( P1_TIEBREAKER, HIGH );
    _pinInterface->pinDigitalWrite( P2_TIEBREAKER, HIGH ); }

void TieBreaker::tieLEDsOff() {
    _gameState->setTieLEDsOn( 0 );
    _pinInterface->pinDigitalWrite( P1_TIEBREAKER, LOW );
    _pinInterface->pinDigitalWrite( P2_TIEBREAKER, LOW ); }

void TieBreaker::celebrate( Player* currentPlayer) {
    std::cout << "*** celebrateWin() called. ***" << std::endl;
    GameTimer::gameDelay( _gameState->getWinDelay() );
    SetWin setWin( &_undo, _gameState, &_setLeds );
    setWin.execute( currentPlayer, _scoreBoard );
    std::cout << "*** done celebrating. *** " << std::endl;
}

void TieBreaker::incrementSet() {
    _gameState->setCurrentSet( _gameState->getCurrentSet() + 1 ); // increment set
}

void TieBreaker::run( Player* currentPlayer ) { 
    _undo.memory(); 
    _gameState->setServe( _getServe()); // set the serve bar depending tie-break iteration
    _scoreBoard->update();
    Player* opponent = currentPlayer->getOpponent();

    if ( currentPlayer->getPoints() == TIE_BREAK_MAX_POINTS ) {
        _undo.snapshot( _history );                                   
        currentPlayer->setGames( currentPlayer->getGames() + 1 );     // increment games
        incrementSet();
        _scoreBoard->update();
        celebrate( currentPlayer );    // this is a win no matter what.
        GameTimer::gameDelay( 3000 );
        endTieBreak(); 
    } else if ( currentPlayer->getPoints() >= TIE_BREAK_WIN_BY_TWO  && 
        ( currentPlayer->getPoints() - opponent->getPoints() >= 2)) {
        _undo.snapshot( _history );                                   
        currentPlayer->setGames( currentPlayer->getGames() + 1 );     // increment games
        incrementSet();
        _scoreBoard->update();
        celebrate( currentPlayer );
        GameTimer::gameDelay( 3000 );
        endTieBreak(); 
    } else {
                               // needed to put this here otherwise tie break would
                               // be incremented even after a win.
        incrementIteration();  // need this to determine serve bar location
    }
}

void TieBreaker::mode1SetTBButtonFunction() {
    switch ( _gameState->getPlayerButton()) {
    case 0:
        break;

    case 1:
        GameTimer::gameDelay( _gameState->getButtonDelay());
        _undo.snapshot( _history );
        _player1->setGames( _player1->getGames() + 1 );
        mode1SetTBP1Games();
        break;

    case 2:
        GameTimer::gameDelay( _gameState->getButtonDelay());
        _undo.mode1Undo( _history );
        break;

    case 3:
        GameTimer::gameDelay( _gameState->getButtonDelay());
        _undo.snapshot( _history );
        _player2->setGames( _player2->getGames() + 1 );
        mode1SetTBP2Games();
        break;

    case 4:
        GameTimer::gameDelay( _gameState->getButtonDelay());
        _undo.mode1Undo( _history );
        break;
    }
    _gameState->setPlayerButton( 0 );
}

void TieBreaker::setTieBreaker() { 
    _undo.memory(); 
    mode1SetTBButtonFunction(); }

void TieBreaker::initializeTieBreakMode() {
    std::cout << "*** initializeTieBreakMode() called. ***" << std::endl;
    _iteration = 1;  // this is initialized to zero before, so it could be checked as another flag
                     // _iteration is used to determine which serve bar to light up
    _player1->setPoints( 0 );
    _player2->setPoints( 0 );
    std::cout << "*** calling _pointLeds.updatePoints() from inside initializeTieBreakMode()... ***" << std::endl;
    _pointLeds.updatePoints();
    std::cout << "*** after update points in tie breaker!!! *** " << std::endl;
    _gameState->setServeSwitch( 1 );
    _gameState->setServe( 0 );
    _serveLeds.serveSwitch();
    if ( _gameState->getTieLEDsOn() == 0 ) { tieLEDsOn(); }
    if( _player1->getGames() != 6 ) {
        std::cout << "*** ERROR: player1 games is not 6 in initializeTieBreakMode() ***  exiting... " << std::endl;
        exit( 1 ); }
    if( _player1->getGames() != 6 ) {
        std::cout << "*** ERROR: player1 games is not 6 in initializeTieBreakMode() ***  exiting... " << std::endl;
        exit( 1 ); }
    _gameLeds.updateGames();
    Inputs _inputs( _player1, _player2, _pinInterface, _gameState );
    WatchTimer _watchTimer;
    for ( int currentPulseCount = 0; currentPulseCount < TIE_PULSE_COUNT; currentPulseCount++ ) {
        tieLEDsOff();
        if ( _watchTimer.watchInputDelay( TIE_BREAK_BLINK_DELAY, &_inputs, TIE_BREAK_WATCH_INTERVAL ) > 0 ) { return; }
        tieLEDsOn();
        if ( _watchTimer.watchInputDelay( TIE_BREAK_BLINK_DELAY, &_inputs, TIE_BREAK_WATCH_INTERVAL ) > 0 ) { return; }}
    _gameLeds.updateGames();
    GameTimer::gameDelay( UPDATE_DISPLAY_DELAY );
    tieLEDsOn(); } // not coming on?

void TieBreaker::setTieBreakEnable() {
    _player1->setPoints( 4 );
    _player2->setPoints( 4 );
    std::cout << "*** calling _pointLeds.updatePoints() from inside setTieBreakEnable()... ***" << std::endl;
    _pointLeds.updatePoints();
    _gameState->setServeSwitch( 1 );
    _gameState->setServe( 0 );
    _serveLeds.serveSwitch();
    Inputs _inputs( _player1, _player2, _pinInterface, _gameState );
    WatchTimer _watchTimer;
    for ( int currentPulseCount = 0; currentPulseCount < TIE_PULSE_COUNT; currentPulseCount++ ) {
        tieLEDsOff();
        if ( _watchTimer.watchInputDelay( TIE_BREAK_BLINK_DELAY, &_inputs, TIE_BREAK_WATCH_INTERVAL ) > 0 ) { return; }
        tieLEDsOn();
        if ( _watchTimer.watchInputDelay( TIE_BREAK_BLINK_DELAY, &_inputs, TIE_BREAK_WATCH_INTERVAL ) > 0 ) { return; }}
    if ( _gameState->getTieLEDsOn() == 0 ) { tieLEDsOn(); }
    _player1->setGames( 0 );
    _player2->setGames( 0 );
    _gameLeds.updateGames();
    GameTimer::gameDelay( UPDATE_DISPLAY_DELAY  ); }

void TieBreaker::endTieBreak() {
    tieLEDsOff();
    _iteration = 0;
    _player1->setPoints( 0 );
    _player2->setPoints( 0 );
    _player1->setGames(  0 );
    _player2->setGames(  0 );
    std::cout << "*** calling _pointLeds.updatePoints() from inside endTieBreak()... ***" << std::endl;
    _pointLeds.updatePoints();
    _gameLeds.updateGames();
    _gameState->setTieBreak(    0 );
    _gameState->setSetTieBreak( 0 );
    _gameState->setServeSwitch( 1 );
    _gameState->setServe( 0 );
    _scoreBoard->update(); }

void TieBreaker::mode1TBP1Games() {
    _gameLeds.updateGames();  // UpdateGames();
    _gameState->setServeSwitch( _gameState->getServeSwitch() + 1 );
    GameTimer::gameDelay( UPDATE_DISPLAY_DELAY );

    if ( _player1->getGames() == 15 ) {
        _player1->setSets( _gameState, _player1->getSets() + 1 );;

        if ( _player2->getSets() == _player1->getSets()) {
            endTieBreak();
            _mode1WinSequences.p1TBSetWinSequence();
            _gameState->setSetTieBreak( 1 );          
            setTieBreakEnable();                     
        } else {
            _mode1WinSequences.p1SetWinSequence();  
            endTieBreak(); }}
    if ( _player1->getGames() >= 10 && ( _player1->getGames() - _player2->getGames() ) > 1 ) {
        _player1->setSets( _gameState, _player1->getSets() + 1 );
        if ( _player2->getSets() == _player1->getSets()) {
            endTieBreak();                         
            _mode1WinSequences.p1TBSetWinSequence(); 
            _gameState->setSetTieBreak( 1 );           
            setTieBreakEnable();                    
        } else {
            _mode1WinSequences.p1SetWinSequence();  
            endTieBreak(); }}}

void TieBreaker::mode1TBP2Games() {
    _gameLeds.updateGames();
    _gameState->setServeSwitch( _gameState->getServeSwitch() + 1 );
    GameTimer::gameDelay( UPDATE_DISPLAY_DELAY );

    if ( _player2->getGames() == 15 ) {
        _player1->setSetHistory( _gameState->getCurrentSet(), _player1->getGames());
        _player2->setSetHistory( _gameState->getCurrentSet(), _player2->getGames());
        _gameState->setCurrentSet( _gameState->getCurrentSet() + 1 );
        _player2->setSets( _gameState, _player2->getSets() + 1 );
        if ( _player2->getSets() == _player1->getSets() ) {
            endTieBreak();                        
            _mode1WinSequences.p2TBSetWinSequence(); 
            _gameState->setSetTieBreak( 1 );
            setTieBreakEnable();
        } else {
            _mode1WinSequences.p2SetWinSequence();
            endTieBreak(); }}
    if ( _player2->getGames() >= 10 && ( _player2->getGames() - _player1->getGames() ) > 1 ) {
        _player1->setSetHistory( _gameState->getCurrentSet(), _player1->getGames());
        _player2->setSetHistory( _gameState->getCurrentSet(), _player2->getGames());
        _gameState->setCurrentSet( _gameState->getCurrentSet() + 1 );
        _player2->setSets( _gameState, _player2->getSets() + 1 );
        if ( _player2->getSets() == _player1->getSets() ) {
            endTieBreak();
            _mode1WinSequences.p2TBSetWinSequence();
            _gameState->setSetTieBreak( 1 );
            setTieBreakEnable();
        } else {
            _mode1WinSequences.p2SetWinSequence();
            endTieBreak();
        }}}

void TieBreaker::mode1SetTBP2Games() {
    _gameLeds.updateGames();
    GameTimer::gameDelay( UPDATE_DISPLAY_DELAY );
    if ( _player2->getGames() == 7 ) {
        std::cout << "inside mode1SetTBP2Games()...  player 2 games  is player 2... 7" << std::endl;
        _player1->setSetHistory( _gameState->getCurrentSet(), _player1->getGames());
        _player2->setSetHistory( _gameState->getCurrentSet(), _player2->getGames());
        _gameState->setCurrentSet( _gameState->getCurrentSet() + 1 );
        _player2->setSets( _gameState, _player2->getSets() + 1 );
        _scoreBoard->update();
        _mode1WinSequences.p2SetTBWinSequence();
        tieLEDsOff();
        _mode1WinSequences.playerTwoMatchWin(); 
        _gameState->stopGameRunning(); }
    _gameState->setServeSwitch( _gameState->getServeSwitch() + 1 ); }

void TieBreaker::mode1SetTBP1Games() {
    _gameLeds.updateGames();
    GameTimer::gameDelay( UPDATE_DISPLAY_DELAY );
    if ( _player1->getGames() == 7 ) {
        std::cout << "inside mode1SetTBP1Games()...  player 1 games  is player 1... 7" << std::endl;
        _player1->setSetHistory( _gameState->getCurrentSet(), _player1->getGames());
        _player2->setSetHistory( _gameState->getCurrentSet(), _player2->getGames());
        _gameState->setCurrentSet( _gameState->getCurrentSet() + 1 );
        _player1->setSets( _gameState, _player1->getSets() + 1 );
        _scoreBoard->update();
        _mode1WinSequences.p1SetTBWinSequence();
        tieLEDsOff();
        _mode1WinSequences.playerOneMatchWin(); 
        _gameState->stopGameRunning(); }
    _gameState->setServeSwitch( _gameState->getServeSwitch() + 1 ); }#ifndef TieBreaker_h
#define TieBreaker_h
#include "../Arduino/Arduino.h"
#include "../GameLeds/GameLeds.h"
#include "../GameLeds/GameLeds.h"
#include "../GameTimer/GameTimer.h"
#include "../PointLeds/PointLeds.h"
#include "../PinInterface/PinInterface.h"
#include "../Player/Player.h"
#include "../ServeLeds/ServeLeds.h"
#include "../SetLeds/SetLeds.h"
#include "../WatchTimer/WatchTimer.h"
#include "../WinSequences/WinSequences.h"
#include "../Undo/Undo.h"
#include "../Inputs/Inputs.h"

class TieBreaker {
 public:
  TieBreaker( Player* player1,
                   Player* player2,
                   PinInterface* pinInterface,
                   GameState* gameState,
                   History* history );
  ~TieBreaker();
  void setScoreBoards( ScoreBoard* scoreBoard );
  void run( Player* currentPlayer );
  void setTieBreaker();
  void buttonAction();
  void mode1SetTBButtonFunction();
  void initializeTieBreakMode();
  void setTieBreakEnable();
  void tieLEDsOn();
  void tieLEDsOff();
  void endTieBreak();
  void mode1TBP1Games();
  void mode1TBP2Games();
  void mode1SetTBP2Games();
  void mode1SetTBP1Games();
  void celebrate( Player* currentPlayer );
  void incrementSet();
  void setIteration( int iteration );
  int  getIteration();
  void incrementIteration();

 private:
  int  _getServe();    // determine serve based on iteration
  Player* _player1;
  Player* _player2;
  PinInterface* _pinInterface;
  GameState* _gameState;
  History* _history;
  PointLeds _pointLeds;
  GameLeds _gameLeds;
  ServeLeds _serveLeds;
  SetLeds _setLeds;
  Mode1WinSequences _mode1WinSequences;
  Undo _undo;
  ScoreBoard* _scoreBoard;
  int _iteration;
};

#endif

#ifndef ArduinoObject_h
#define ArduinoObject_h

#include <iostream>
#include <string>
#define OUTPUT 0
#define LOW 0
#define HIGH 1
// #include "GameTimer.h"

class ArduinoObject {
 public:
  ArduinoObject();
  ~ArduinoObject();
  void gameDelay(int timeToDelay);
  int gameMillis();
  void logUpdate(std::string message);
};

#endif


#include "Arduino.h"

ArduinoObject::ArduinoObject() {}
ArduinoObject::~ArduinoObject() {}
void ArduinoObject::gameDelay(int timeToDelay) {
  std::cout << "Sleeping for " << timeToDelay << " milliseconds" << std::endl;
}
int ArduinoObject::gameMillis() {
  std::cout << "gameMillis() called..." << std::endl;
  return 1000;
}

void ArduinoObject::logUpdate(std::string message) {
  std::cout << message << std::endl;
}
#include "PointLeds.h"

PointLeds::PointLeds( Player* player1,
    Player* player2,
    PinInterface* pinInterface )
    : _player1( player1 ), _player2( player2 ), _pinInterface( pinInterface ) {
    _scoreBoardSet = false;
    }

PointLeds::PointLeds( Player* player1,
    Player* player2,
    ScoreBoard* scoreBoard )
    : _player1( player1 ), _player2( player2 ), _scoreBoard(   scoreBoard   ) {
    _scoreBoardSet = true;
    }


PointLeds::~PointLeds() {}

void PointLeds::setScoreBoard( ScoreBoard* scoreBoard ) { 
    std::cout << "*** setting _scoreBoard in PointLeds object ... ***" << std::endl;
    _scoreBoard = scoreBoard; 
    _scoreBoardSet = true; }

void PointLeds::updatePoints() {
    std::cout << "calling _scoreBoard->update() from inside PointLeds.  checking scoreboard bool.. " << std::endl;
    if ( _scoreBoardSet == true ) { /* std::cout << "scoreboard bool is true" << std::endl; */ }
    else { std::cout << "scoreboard bool is false" << std::endl; exit( 1 ); }
    _scoreBoard->update();
    // std::cout << "done calling _scoreBoard->update()... \n\n" << std::endl;
    return;
    
    switch ( _player1->getPoints()) {
    case 0:
        // draw "00"
        break;
    case 1:
        // draw "10"
        break;
    case 2:
        // draw "15"
        break;
    case 3:
        // draw "30"
        break;
    case 4:
        // draw "40"
        break;
    case 5:
        // draw "40"
        break;

    case 99:
        // draw "Ad"
        break;

    case 100:
        // draw "blank"
        break;
    }

    switch ( _player2->getPoints() ) {
    case 0:
        // draw "00"
        break;
    case 1:
        // draw "10"
        break;
    case 2:
        // draw "15"
        break;
    case 3:
        // draw "30"
        break;
    case 4:
        // draw "40"
        break;
    case 5:
        // draw "40"
        break;
    case 99:
        // draw "Ad"
        break;

    case 100:
        // draw "blank"
        break;
    }
}

void PointLeds::updateTBPoints() {
    // update tie breaker points
}
#ifndef PointLeds_h
#define PointLeds_h

#include "../GameState/GameState.h"
#include "../PinInterface/PinInterface.h"
#include "../Player/Player.h"
#include "../Arduino/Arduino.h"
#include "../ScoreBoard/ScoreBoard.h"

class PointLeds {
 public:
  PointLeds( Player* player1, Player* player2, PinInterface* pinInterface );
  PointLeds( Player* player1, Player* player2, ScoreBoard*   scoreBoard   );
  ~PointLeds();
  void updatePoints();
  void updateTBPoints();
  void setScoreBoard( ScoreBoard* scoreBoard );

 private:
  Player* _player1;
  Player* _player2;
  PinInterface* _pinInterface;
  ScoreBoard* _scoreBoard;
  bool _scoreBoardSet;
};

#endif#include "SetLeds.h"
#include "../Arduino/Arduino.h"
#include "../TennisConstants/TennisConstants.h"

SetLeds::SetLeds( Player* player1, Player* player2, PinInterface* pinInterface )
    : _player1( player1 ), _player2( player2 ), _pinInterface( pinInterface) {}

SetLeds::~SetLeds(){}

void SetLeds::setScoreBoard( ScoreBoard* scoreBoard ) { _scoreBoard = scoreBoard; }

#define PLAYER_1_ZERO_SETS 0
#define PLAYER_1_ONE_SET   1
#define PLAYER_1_TWO_SETS  2
#define PLAYER_2_ZERO_SETS 0
#define PLAYER_2_ONE_SET   1
#define PLAYER_2_TWO_SETS  2

void SetLeds::updateSets() {
  // std::cout << "inside SetLeds::updateSets()" << std::endl;
  // std::cout << "player1 sets: " << _player1->getSets() << std::endl;
  if( !_scoreBoard ) {
    // std::cout << "scoreboard is null" << std::endl;
  } else { std::cout << "scoreboard is not null" << std::endl;  }
  switch ( _player1->getSets() ) {

    case PLAYER_1_ZERO_SETS:
        std::cout << "player1 has zero sets" << std::endl;
        if ( _scoreBoard->hasCanvas() ) {
            std::cout << "scoreboard has canvas.  updating..." << std::endl;
            _scoreBoard->update();
        } else {
            _pinInterface->pinDigitalWrite( P1_SETS_LED1, LOW );
            _pinInterface->pinDigitalWrite( P1_SETS_LED2, LOW ); } break;

    case PLAYER_1_ONE_SET:
        std::cout << "player1 has one set" << std::endl;
        if ( _scoreBoard->hasCanvas() ) {
            std::cout << "scoreboard has canvas.  updating..." << std::endl;
            _scoreBoard->update();
        } else {
            _pinInterface->pinDigitalWrite( P1_SETS_LED1, HIGH );
            _pinInterface->pinDigitalWrite( P1_SETS_LED2, LOW ); } break;

    case PLAYER_1_TWO_SETS:
        // std::cout << "player1 has two sets" << std::endl;
        if ( _scoreBoard->hasCanvas() ) {
            std::cout << "scoreboard has canvas.  updating..." << std::endl;
            _scoreBoard->update();
        } else {
            _pinInterface->pinDigitalWrite( P1_SETS_LED1, HIGH );
            _pinInterface->pinDigitalWrite( P1_SETS_LED2, HIGH ); } break;
    case 3:
        std::cout << "player1 has three sets" << std::endl;
        if ( _scoreBoard->hasCanvas() ) {
            std::cout << "scoreboard has canvas.  updating..." << std::endl;
            _scoreBoard->update();
        } else {
            _pinInterface->pinDigitalWrite( P1_SETS_LED1, HIGH );
            _pinInterface->pinDigitalWrite( P1_SETS_LED2, HIGH ); } break;
  }

  switch (_player2->getSets()) {
    case PLAYER_2_ZERO_SETS:
        // std::cout << "player2 has zero sets" << std::endl;
        if ( _scoreBoard->hasCanvas() ) {
            std::cout << "scoreboard has canvas.  updating..." << std::endl;
            _scoreBoard->update();
        } else {
            _pinInterface->pinDigitalWrite( P2_SETS_LED1, LOW );
            _pinInterface->pinDigitalWrite( P2_SETS_LED2, LOW ); } break;
            
    case PLAYER_2_ONE_SET:
        std::cout << "player2 has one set" << std::endl;
        if ( _scoreBoard->hasCanvas() ) {
            std::cout << "scoreboard has canvas.  updating..." << std::endl;
            _scoreBoard->update();
        } else {
            _pinInterface->pinDigitalWrite( P2_SETS_LED1, HIGH );
            _pinInterface->pinDigitalWrite( P2_SETS_LED2, LOW ); } break;

    case PLAYER_2_TWO_SETS:
        std::cout << "player2 has two sets" << std::endl;
        if ( _scoreBoard->hasCanvas() ) {
            std::cout << "scoreboard has canvas.  updating..." << std::endl;
            _scoreBoard->update();
        } else {
            _pinInterface->pinDigitalWrite( P2_SETS_LED1, HIGH );
            _pinInterface->pinDigitalWrite( P2_SETS_LED2, HIGH ); } break;
    case 3:
        std::cout << "player2 has three sets" << std::endl;
        if ( _scoreBoard->hasCanvas() ) {
            std::cout << "scoreboard has canvas.  updating..." << std::endl;
            _scoreBoard->update();
        } else {
            _pinInterface->pinDigitalWrite( P2_SETS_LED1, HIGH );
            _pinInterface->pinDigitalWrite( P2_SETS_LED2, HIGH ); } break; }}#ifndef SetLeds_h
#define SetLeds_h

#include "../Arduino/Arduino.h"
#include "../PinInterface/PinInterface.h"
#include "../Player/Player.h"
#include "../ScoreBoard/ScoreBoard.h"

class SetLeds {
 public:
  SetLeds( Player* player1, Player* player2, PinInterface* pinInterface );
  ~SetLeds();
  void updateSets();
  void setScoreBoard( ScoreBoard* scoreBoard );

 private:
  Player*       _player1;
  Player*       _player2;
  PinInterface* _pinInterface;
  ScoreBoard*   _scoreBoard; };
#endif#include "PinInterface.h"
#include <string>

PinInterface::PinInterface( PinState* pinState ) : _pinState( pinState ) {}
PinInterface::~PinInterface() {}

int PinInterface::pinAnalogRead( int pin ) {
    std::string pin_string = std::to_string( pin );
    int pin_value = _pinState->getPinState( pin_string );
    return pin_value; }

int PinInterface::pinDigitalRead( int pin ) {
    int pin_value = _pinState->getPinState( std::to_string( pin ));
    return pin_value; }

void PinInterface::pinAnalogWrite( int pin, int value ) { _pinState->setPinState( std::to_string( pin ), value ); }

void PinInterface::pinDigitalWrite( int pin, int value ) { _pinState->setPinState( std::to_string( pin ), value ); }

std::map<std::string, int> PinInterface::getPinStateMap() { return _pin_map; }
#ifndef PININTERFACE_H
#define PININTERFACE_H

#include "../PinState/PinState.h"
#include "../Arduino/Arduino.h"
#include <map>

class PinInterface {
  public:
    PinInterface(PinState* pinState);
    ~PinInterface();
    void pinAnalogWrite(int pin, int value);
    void pinDigitalWrite(int pin, int value);
    int pinAnalogRead(int pin);
    int pinDigitalRead(int pin);
    std::map<std::string, int> getPinStateMap();

  private:
    std::map<std::string, int> _pin_map;
    PinState* _pinState;
};

#endif
#include "ServeLeds.h"

ServeLeds::ServeLeds(PinInterface* pinInterface, GameState* gameState)
    : _pinInterface(pinInterface), _gameState(gameState) {}
ServeLeds::~ServeLeds() {}

void ServeLeds::updateServeLED() {
  if (_gameState->getServe() /* serve */ == 0) {
    if( _gameState->getCurrentAction().find( "2 scored" ) != std::string::npos ) { // ERROR trap.
      std::cout << "*** ERROR: Player 2 scored yet we are turning player 1 server bar on.  exiting program... ***" << std::endl;
      exit( 1 ); }  

    _pinInterface->pinDigitalWrite(P1_SERVE, HIGH);
    _pinInterface->pinDigitalWrite(P2_SERVE, LOW);
  } else {
    if( _gameState->getCurrentAction().find( "1 scored" ) != std::string::npos ) { // ERROR trap.
      std::cout << "*** ERROR: Player 1 to scored yet we are turning player 2 serve bar on.  exiting program... ***" << std::endl;
      /* exit( 1 );*/ } 

    std::cout << "updateServeLED() setting P2_SERVE to HIGH" << std::endl;
    _pinInterface->pinDigitalWrite(P1_SERVE, LOW);
    _pinInterface->pinDigitalWrite(P2_SERVE, HIGH);
  }
}

void ServeLeds::serveSwitch() {
//   std::cout << "inside serveSwitch()..." << std::endl;
  if (_gameState->getServeSwitch() /* serveSwitch */ >= 2) {
    if (_gameState->getServe() /* serve */ == 0) {
    //   std::cout << "serveSwitch() setting serve to 1" << std::endl;
      _gameState->setServe( 1 );  // serve = 1;
    } else {
    //   std::cout << "serveSwitch() setting serve to 0" << std::endl;
      _gameState->setServe( 0 );  // serve = 0;
    }
    // std::cout << "serveSwitch() setting serveSwitch to 0" << std::endl;
    _gameState->setServeSwitch( 0 );  // serveSwitch = 0;

    // std::cout << "calling updateServeLED() from serveSwitch()... " << std::endl;
    updateServeLED();
  }
}
#ifndef SERVE_LEDS_h
#define SERVE_LEDS_h

#include "../GameState/GameState.h"
#include "../PinInterface/PinInterface.h"
#include "../Arduino/Arduino.h"
#include "../TennisConstants/TennisConstants.h"

class ServeLeds {
 public:
  ServeLeds(PinInterface* pinInterface, GameState* gameState);
  ~ServeLeds();
  void updateServeLED();
  void serveSwitch();

 private:
  PinInterface* _pinInterface;
  GameState* _gameState;
};

#endif
#ifndef WatchTimer_H
#define WatchTimer_H
#include "../TennisConstants/TennisConstants.h"
#include "../Inputs/Inputs.h"
#include "../GameTimer/GameTimer.h"

class WatchTimer {
 public:
  WatchTimer();
  ~WatchTimer();

  int watchInputDelay( int delay, Inputs* input, int watchInterval );

};

#endif
#include "WatchTimer.h"

WatchTimer::WatchTimer() {}
WatchTimer::~WatchTimer() {}

int WatchTimer::watchInputDelay( int delay, Inputs* input, int watchInterval  ) {
    int initialRotaryValue = input->readRotary();
    int totalDelay = 0;
    while ( totalDelay < delay ) {
        GameTimer::gameDelay( watchInterval );
        if ( input->readRotary() != initialRotaryValue ) { return 1; }
        totalDelay += watchInterval;
    }
    return 0; }
#ifndef GAME_LED_HEADER_H
#define GAME_LED_HEADER_H

#include "../PinInterface/PinInterface.h"
#include "../Player/Player.h"
#include "../Arduino/Arduino.h"
#include "../TennisConstants/TennisConstants.h"
#include "../ScoreBoard/ScoreBoard.h"
#include "../GameLedTranslator/GameLedTranslator.h"

class GameLeds {
 public:
  GameLeds( Player* player1, Player* player2, PinInterface* pinInterface );
  ~GameLeds();
  void updateGames();
  void setScoreBoard( ScoreBoard* scoreBoard );
  ScoreBoard* getScoreBoard();

 private:
  Player*            _player1;
  Player*            _player2;
  PinInterface*      _pinInterface;
  ScoreBoard*        _scoreBoard;
  GameLedTranslator* _gameLedTranslator;
};

#endif
#include "GameLeds.h"

GameLeds::~GameLeds() { delete _gameLedTranslator; }

GameLeds::GameLeds( Player* player1, Player* player2, PinInterface* pinInterface )
    : _player1( player1), _player2( player2 ), _pinInterface( pinInterface ) {
    _gameLedTranslator = new GameLedTranslator( player1, player2, pinInterface ); }

void GameLeds::setScoreBoard( ScoreBoard* scoreBoard ) { _scoreBoard = scoreBoard; }
ScoreBoard* GameLeds::getScoreBoard() { return _scoreBoard; }

void GameLeds::updateGames() {
    if ( _scoreBoard        == NULL ) { std::cout << "*** ERROR: scoreBoard is null. ***  exiting... " << std::endl; exit( 1 ); }
    if ( _gameLedTranslator == NULL ) { std::cout << "*** ERROR: _gameLedTranslator is null. ***  exiting... " << std::endl; exit( 1 ); }
    if ( _scoreBoard->hasCanvas()) { _scoreBoard->update();
    } else { _gameLedTranslator->drawGameLeds(); }}
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
    void snapshot( History* history );
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
#endif#include "Undo.h"

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
    // std::cout << "*** Undo destructor called. ***" << std::endl;
    delete _logger; };

void Undo::setScoreBoard( ScoreBoard* scoreBoard ) {
    // _scoreBoard = scoreBoard;
    _pointLeds.setScoreBoard(          scoreBoard ); 
    _gameLeds.setScoreBoard(           scoreBoard ); 
    // _mode1WinSequences.setScoreBoards( scoreBoard ); 
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

void Undo::snapshot( History* history ) {
    GameState gameState;
    gameState.setPlayer1Points( _player1->getPoints()); gameState.setP1PointsMem( _gameState->getP1PointsMem());
    gameState.setPlayer2Points( _player2->getPoints()); gameState.setP2PointsMem( _gameState->getP2PointsMem());
    gameState.setPlayer1Games( _player1->getGames());  gameState.setP1GamesMem( _gameState->getP1GamesMem());
    gameState.setPlayer2Games( _player2->getGames()); gameState.setP2GamesMem( _gameState->getP2GamesMem());
    gameState.setPlayer1Sets( _player1->getSets()); gameState.setP1SetsMem( _gameState->getP1SetsMem());
    gameState.setPlayer2Sets( _player2->getSets()); gameState.setP2SetsMem( _gameState->getP2SetsMem());
    gameState.setPlayer1Matches( _player1->getMatches()); gameState.setPlayer2Matches( _player2->getMatches());
    // std::cout << "setting serve to " << _gameState->getServe() << std::endl;
    gameState.setServe( _gameState->getServe());
    // std::cout << "setting serve switch to " << _gameState->getServeSwitch() << std::endl;
    gameState.setServeSwitch( _gameState->getServeSwitch());
    // std::cout << "done setting serve and serve switch.  setting undo..." << std::endl;
    gameState.setUndo( _gameState->getUndo());
    // std::cout << "done setting undo.  setting started..." << std::endl;
    gameState.setStarted( _gameState->getStarted());
    gameState.setPointFlash( _gameState->getPointFlash());
    gameState.setRotaryPosition( _gameState->getRotaryPosition());
    gameState.setPrevRotaryPosition( _gameState->getPrevRotaryPosition());
    gameState.setRotaryChange( _gameState->getRotaryChange());
    gameState.setToggle( _gameState->getToggle());
    gameState.setTieLEDsOn( _gameState->getTieLEDsOn());
    // gameState.setPlayerButton( _gameState->getPlayerButton()); // this is breaking the undo
    gameState.setTieBreak( _gameState->getTieBreak());
    gameState.setSetTieBreak( _gameState->getSetTieBreak());
    gameState.setSetTieBreakMem( _gameState->getSetTieBreakMem());
    gameState.setTieBreakOnly( _gameState->getTieBreakOnly());
    gameState.setTieBreakMem( _gameState->getTieBreakMem());
    // std::cout << "setting set histories..." << std::endl;
    gameState.setPlayer1SetHistory( _player1->getSetHistory());
    gameState.setPlayer2SetHistory( _player2->getSetHistory());

    _gameState->setPlayer1SetHistory( _player1->getSetHistory());
    _gameState->setPlayer2SetHistory( _player2->getSetHistory());
    gameState.setCurrentSet( _gameState->getCurrentSet());
    // std::cout << "done setting set histories.  pushing gamestate to history..." << std::endl;
    history->push( gameState ); 
    
    
    // print size of gamestate
    // std::cout << "gamestate size: " << sizeof( gameState ) << std::endl;
    // std::cout << "done pushing gamestate to history." << std::endl; 
}

void Undo::mode1Undo( History* history ) {
    GameTimer::gameDelay( 100 );
    if ( history->size() == 0 ) { return; }
    // std::cout << "inside mode1Undo.  history->size()==" << history->size() << std::endl;
    if ( _scoreBoardSet == false ) { std::cout << "*** ERROR: trying to call undo when _scoreBoardSet == false exiting process... *** \nMake sure to call undo->setScoreBoard before trying to use the Undo object." << std::endl; exit( 1 ); } // TODO: Update Current Set 1st!
    GameState gameState = ( history->pop());
    _gameState->setCurrentSet( gameState.getCurrentSet());
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
    // _gameState->setPlayerButton( gameState.getPlayerButton()); // this is breaking the undo
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
}#include "PinInterface.h"
#include <string>

PinInterface::PinInterface( PinState* pinState ) : _pinState( pinState ) {}
PinInterface::~PinInterface() {}

int PinInterface::pinAnalogRead( int pin ) {
    std::string pin_string = std::to_string( pin );
    int pin_value = _pinState->getPinState( pin_string );
    return pin_value; }

int PinInterface::pinDigitalRead( int pin ) {
    int pin_value = _pinState->getPinState( std::to_string( pin ));
    return pin_value; }

void PinInterface::pinAnalogWrite( int pin, int value ) { _pinState->setPinState( std::to_string( pin ), value ); }

void PinInterface::pinDigitalWrite( int pin, int value ) { _pinState->setPinState( std::to_string( pin ), value ); }

std::map<std::string, int> PinInterface::getPinStateMap() { return _pin_map; }
#ifndef PININTERFACE_H
#define PININTERFACE_H

#include "../PinState/PinState.h"
#include "../Arduino/Arduino.h"
#include <map>

class PinInterface {
  public:
    PinInterface(PinState* pinState);
    ~PinInterface();
    void pinAnalogWrite(int pin, int value);
    void pinDigitalWrite(int pin, int value);
    int pinAnalogRead(int pin);
    int pinDigitalRead(int pin);
    std::map<std::string, int> getPinStateMap();

  private:
    std::map<std::string, int> _pin_map;
    PinState* _pinState;
};

#endif
#include "GameTimer.h"

GameTimer::GameTimer() {}
GameTimer::~GameTimer(){}

void GameTimer::gameDelay( int milliseconds ) { 
    std::this_thread::sleep_for( std::chrono::milliseconds( milliseconds )); }

void GameTimer::sleep_until( int milliseconds ) {}

unsigned long GameTimer::gameMillis() {
    std::chrono::milliseconds ms =
    std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch());
    return ms.count(); }#ifndef GameTimer_h
#define GameTimer_h
#include <chrono>
#include <thread>

class GameTimer {
 public:
  GameTimer();
  void sleep_until(int milliseconds);
  static void gameDelay(int milliseconds);
  static unsigned long gameMillis();
  ~GameTimer();
};

#endif
#ifndef Player_h
#define Player_h

#include "../GameState/GameState.h"
#include "../TennisConstants/TennisConstants.h"
#include <map>

class GameState;
class Player {
public:
    Player( GameState* gameState, int player_number );
    ~Player();
    
    void setOpponent(    Player* opponent                 );
    Player* getOpponent();

    void setSets( GameState* gameState, int sets );
    int getSets();

    void setPoints( int points  );
    int getPoints();

    void setGames( int game_value  ); // it knows the current set
    int getGames();

    void setServeSwitch( int serve_switch                 );
    int getServeSwitch();

    void setMatches(     int matches );
    int getMatches();

    void setMode(        int mode    );
    int getMode();

    void setSetting(     int setting );
    int getSetting();

    void setSetHistory(  int set, int score               );
    std::map<int, int> getSetHistory();

    void setGameHistory( int game, int score              );
    std::map<int, int> getGameHistory();

    int incrementSetting();

    int number(); // only set during construction

private:
    GameState* _gameState;
    int _playerNumber;
    Player* _opponent;
    int _points;
    int _games;
    int _sets;
    int _matches;
    int _mode;
    int _setting;
    int _serve_switch;
    std::map<int, int> _set_history;
    std::map<int, int> _game_history;
};

#endif#include "Player.h"

Player::Player( GameState* gamestate, int playerNumber ) : _gameState( gamestate ), _playerNumber( playerNumber ) {
        _points = 0; _games = 0; _sets = 0; _matches = 0; _mode = 0; _setting = 0; 
        _game_history[ 1 ] = 0; _game_history[ 2 ] = 0; _game_history[ 3 ] = 0;     // initialize game history
        _set_history[  1 ] = 0;  _set_history[ 2 ] = 0; _set_history[  3 ] = 0; }   // initialize set history
Player::~Player() {}

void Player::setServeSwitch( int serve_switch ) { _serve_switch = serve_switch; } 
int Player::getServeSwitch() { return _serve_switch; }
void Player::setOpponent( Player* opponent ) { _opponent = opponent; }                                  
Player* Player::getOpponent() { return _opponent; }
void Player::setSets( GameState* gameState, int sets ) {                         // sets this player's sets
    this->setSetHistory(      gameState->getCurrentSet(), _games               ); // and set history for both
    _opponent->setSetHistory( gameState->getCurrentSet(), _opponent->getGames()); // players
    if( _playerNumber == PLAYER_1_INITIALIZED ) { 
        gameState->setPlayer1SetHistory( this->getSetHistory());
        gameState->setPlayer2SetHistory( _opponent->getSetHistory()); }
    else {
        gameState->setPlayer1SetHistory( _opponent->getSetHistory());
        gameState->setPlayer2SetHistory( this->getSetHistory()); }
    _sets = sets; }                                          
int Player::getSets() { return _sets; }

void Player::setPoints(int points) { _points = points; } 
int Player::getPoints() {  return _points;  }

void Player::setGames( int games ) { 
    _set_history[ _gameState->getCurrentSet()] = games;
    number() == PLAYER_1_INITIALIZED ? 
        _gameState->setPlayer1Games( games ) : _gameState->setPlayer2Games( games );
    _games = games; }         

int Player::getGames() { return _games; }

void Player::setMatches(int matches) { _matches = matches; } int Player::getMatches() { return _matches; }
void Player::setMode(int mode) { _mode = mode; }             int Player::getMode() {    return _mode;    }
void Player::setSetting(int setting) { _setting = setting; } int Player::getSetting() { return _setting; }
int Player::incrementSetting() { return ++_setting; }
int Player::number() { 
    // std::cout << "Player::number() returning " << _playerNumber << std::endl;
    return _playerNumber; }

void Player::setSetHistory( int set, int games ) {
    std::cout << "setting set history for player " << number() << " set " << set << " to " << games << std::endl;
    _set_history[  set ] = games; 
    number() == PLAYER_1_INITIALIZED ? 
        _gameState->setPlayer1SetHistory( _set_history ) : _gameState->setPlayer2SetHistory( _set_history ); } 
std::map< int, int> Player::getSetHistory() { 
    return _set_history; }

void Player::setGameHistory( int game, int score ) { _game_history[ game ] = score; } 
std::map< int, int> Player::getGameHistory() { return _game_history;}