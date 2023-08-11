#ifndef SERVE_LEDS_h
#define SERVE_LEDS_h

#include "../GameState/GameState.h"
#include "../PinInterface/PinInterface.h"
#include "../Arduino/Arduino.h"
#include "../TennisConstants/TennisConstants.h"

class ServeLeds {
 public:
  ServeLeds( IPinInterface* pinInterface, IGameState* gameState);
  ~ServeLeds();
  void updateServeLED();
  void serveSwitch();

 private:
  IPinInterface* _pinInterface;
  IGameState* _gameState;
};

#endif
