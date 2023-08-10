#ifndef SERVE_LEDS_h
#define SERVE_LEDS_h

#include "../GameState/IGameState.h"
#include "../PinInterface/IPinInterface.h"
#include "../Arduino/Arduino.h"
#include "../TennisConstants/TennisConstants.h"

class ServeLeds {
 public:
  ServeLeds( IPinInterface* pinInterface, IGameState* gameState);
  ~ServeLeds();
  void updateServeLED();
  void serveSwitch();

 private:
  PinInterface* _pinInterface;
  GameState* _gameState;
};

#endif
