#ifndef MODE_1_SCORE_H
#define MODE_1_SCORE_H

#include "../Arduino/Arduino.h"
#include "../GameLeds/GameLeds.h"
#include "../GameState/GameState.h"
#include "../GameTimer/GameTimer.h"
#include "../Mode1Tiebreaker/Mode1Tiebreaker.h"
#include "../WinSequences/WinSequences.h"
#include "../PointLeds/PointLeds.h"
#include "../PinInterface/PinInterface.h"
#include "../Player/Player.h"
#include "../SetLeds/SetLeds.h"
#include "../Undo/Undo.h"
#include "../TennisConstants/TennisConstants.h"
#include <iostream>

class Mode1Score {
 public:
    Mode1Score( IPlayer* player1,
                IPlayer* player2,
                PinInterface* pinInterface,
                GameState* gameState,
                History* history );
    ~Mode1Score();
    void mode1P1Score();
    void mode1P1Games();
    void mode1TBP1Games();
    void mode1SetTBP1Games();
    void mode1P2Score();
    void mode1P2Games();
    void mode1TBP2Games();
    void mode1SetTBP2Games();
    void setScoreBoard( ScoreBoard* scoreBoard );
    void updateScore(   IPlayer* currentPlayer  );

 private:
    void _resetGame();
    IPlayer* _player1;
    IPlayer* _player2;
    GameState* _gameState;
    History* _history;
    Mode1TieBreaker _mode1TieBreaker;
    PointLeds _pointLeds;
    GameLeds _gameLeds;
    SetLeds _setLeds;
    WinSequences _mode1WinSequences;
    Undo _undo;
    ScoreBoard* _scoreBoard; };
#endif
