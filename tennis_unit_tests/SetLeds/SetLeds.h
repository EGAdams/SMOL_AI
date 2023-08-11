#ifndef SetLeds_h
#define SetLeds_h

#include "../Arduino/Arduino.h"
#include "../PinInterface/PinInterface.h"
#include "../Player/Player.h"
#include "../ScoreBoard/ScoreBoard.h"

class SetLeds {
 public:
  SetLeds( IPlayer* player1, IPlayer* player2, IPinInterface* pinInterface );
  ~SetLeds();
  void updateSets();
  void setScoreBoard( ScoreBoard* scoreBoard );

 private:
  IPlayer*       _player1;
  IPlayer*       _player2;
  IPinInterface* _pinInterface;
  ScoreBoard*   _scoreBoard; };
#endif