#ifndef SetWin_h
#define SetWin_h

#include "../Arduino/Arduino.h"
#include "../Player/Player.h"
#include "../GameState/GameState.h"
#include "../GameTimer/GameTimer.h"
#include "../Undo/Undo.h"
#include "../SetLeds/SetLeds.h"
#include <iostream>

class SetWin {

 public:
  SetWin( Undo* undo, IGameState gameState, SetLeds* setLeds );
  ~SetWin();
  void execute( IPlayer* player );

 private:
     Undo*      _undo; 
     IGameState _gameState; 
     SetLeds*   _setLeds; };
#endif