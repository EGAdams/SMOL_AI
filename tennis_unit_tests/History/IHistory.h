#ifndef IHISTORY_H
#define IHISTORY_H

#include "../googletest/googlemock/include/gmock/gmock.h"
#include <string>
#include <vector>
#include "../GameState/GameState.h"

class IHistory {
public:
    virtual ~IHistory() {}
    virtual void push( GameState gameState );
    virtual GameState pop();
    virtual int size() = 0; };
#endif // IHISTORY_H