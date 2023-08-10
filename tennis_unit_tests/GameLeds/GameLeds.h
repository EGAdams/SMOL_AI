#ifndef GAME_LED_HEADER_H
#define GAME_LED_HEADER_H

#include "../PinInterface/IPinInterface.h"
#include "../Player/Player.h"
#include "../Arduino/Arduino.h"
#include "../TennisConstants/TennisConstants.h"
#include "../ScoreBoard/ScoreBoard.h"
#include "../GameLedTranslator/GameLedTranslator.h"

class GameLeds {
 public:
  GameLeds( IPlayer* player1, IPlayer* player2, IPinInterface* pinInterface );
  ~GameLeds();
  void updateGames();
  void setScoreBoard( ScoreBoard* scoreBoard );

 private:
  IPlayer*            _player1;
  IPlayer*            _player2;
  IPinInterface*      _pinInterface;
  ScoreBoard*        _scoreBoard;
  GameLedTranslator* _gameLedTranslator;
};

#endif