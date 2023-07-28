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
  Mode1Functions(Player* player1,
                 Player* player2,
                 PinInterface* pinInterface,
                 GameState* gameState,
                 History* history);
  ~Mode1Functions();
  void mode1ButtonFunction();
  void mode1ServeFunction();
  void pointFlash();

 private:
  Player* _player1;
  Player* _player2;
  GameState* _gameState;
  History* _history;
  Undo _undo;
  PointLeds _pointLeds;
  Mode1Score _mode1Score;
  ServeLeds _serveLeds;
};

#endif