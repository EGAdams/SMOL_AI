#ifndef MatchWinSequence_h
#define MatchWinSequence_h

#include "../Arduino/Arduino.h"
#include "../TennisConstants/TennisConstants.h"
#include "../GameTimer/GameTimer.h"
#include "../Player/Player.h"
#include "../GameState/GameState.h"
#include "../GameLeds/GameLeds.h"
#include "../SetLeds/SetLeds.h"

class MatchWinSequence {

 public:
  MatchWinSequence();
  ~MatchWinSequence();
  void run( IPlayer* player, IGameState* gameState, GameLeds* gameLeds, SetLeds* setLeds );

 private:

};
#endif
