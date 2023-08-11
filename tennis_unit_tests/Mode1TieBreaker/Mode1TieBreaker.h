#ifndef Mode1TieBreaker_h
#define Mode1TieBreaker_h
#include "../Arduino/Arduino.h"
#include "../GameLeds/GameLeds.h"
#include "../GameTimer/GameTimer.h"
#include "../PointLeds/PointLeds.h"
#include "../PinInterface/IPinInterface.h"
#include "../Player/Player.h"
#include "../ServeLeds/ServeLeds.h"
#include "../SetLeds/SetLeds.h"
#include "../WatchTimer/WatchTimer.h"
#include "../WinSequences/WinSequences.h"
#include "../Undo/Undo.h"
#include "../Inputs/Inputs.h"
#include "../History/History.h"

class Mode1TieBreaker {
 public:
  Mode1TieBreaker( IPlayer* player1,
                   IPlayer* player2,
                   IPinInterface* pinInterface,
                   IGameState* gameState,
                   IHistory* history );
  ~Mode1TieBreaker();
  void tieBreaker();
  void setTieBreaker();
  void mode1TBButtonFunction();
  void mode1SetTBButtonFunction();
  void tieBreakEnable();
  void setTieBreakEnable();
  void tieLEDsOn();
  void tieLEDsOff();
  void endTieBreak();

  // from mode 1 score
  void mode1TBP1Games();
  void mode1TBP2Games();
  void mode1SetTBP2Games();
  void mode1SetTBP1Games();

  // from mode 1 win sequences
  // void p1TBSetWinSequence();
  // void p1SetWinSequence();
  // void p2TBSetWinSequence();
  // void p2SetWinSequence();

 private:
  IPlayer* _player1;
  IPlayer* _player2;
  IPinInterface* _pinInterface;
  IGameState* _gameState;
  IHistory* _history;
  PointLeds _pointLeds;
  GameLeds _gameLeds;
  ServeLeds _serveLeds;
  SetLeds _setLeds;
  WinSequences _mode1WinSequences;
  Undo _undo;
};

#endif
