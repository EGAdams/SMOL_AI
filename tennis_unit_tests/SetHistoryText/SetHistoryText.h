#ifndef SET_HISTORY_TEXT_H
#define SET_HISTORY_TEXT_H

#include <string>
#include <map>
#include "../GameState/GameState.h"
#include "../TennisConstants/TennisConstants.h"

class SetHistoryText {
 public:
    SetHistoryText( IGameState* gameState );
    ~SetHistoryText();
    std::string getSetHistoryText( int player );
    std::string _buildString(      int player );

 private: 
    IGameState* _gameState; };
#endif