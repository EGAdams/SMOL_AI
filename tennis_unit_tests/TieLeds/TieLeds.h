//
// class TieLeds
//
#ifndef TIE_LEDS_H
#define TIE_LEDS_H

#include "../Arduino/Arduino.h"
#include "../PinInterface/PinInterface.h"
#include "../TennisConstants/TennisConstants.h"

class TieLeds {
 public:
  TieLeds( IPinInterface* pinInterface );
  ~TieLeds();
  void turnOff();
  void turnOn();

 private:
  IPinInterface* _pinInterface;
};

#endif
