#ifndef MODE_1_FUNCTIONS_h
#define MODE_1_FUNCTIONS_h
#include "Arduino.h"
#include "GameState.h"
#include "GameTimer.h"
#include "MODE_1_SCORE.h"
#include "POINT_LEDs.h"
#include "PinInterface.h"
#include "UNDO.h"
class History;
class Mode1Functions {
 public:
  Mode1Functions( IPlayer* player1,
                  IPlayer* player2,
                  IPinInterface* pinInterface,
                  IGameState* gameState,
                  IHistory* history);
  ~Mode1Functions();
  void mode1ButtonFunction();
  void mode1ServeFunction();
  void pointFlash();

 private:
  IPlayer* _player1;
  IPlayer* _player2;
  IGameState* _gameState;
  IHistory* _history;
  Undo _undo;
  PointLeds _pointLeds;
  Mode1Score _mode1Score;
  ServeLeds _serveLeds;
};

#endif