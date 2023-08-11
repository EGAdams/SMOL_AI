#ifndef History_h
#define History_h

#include "IHistory.h"
#include <stack>
#include "IHistory.h"
#include "../GameState/GameState.h"
#include "../Logger/Logger.h"

class History : public IHistory {
 public:
    History();
    ~History();
    void push( GameState gameState );
    GameState pop();
    int size();

 private:
    std::stack< GameState > _history;
    Logger* _logger; };
#endif
