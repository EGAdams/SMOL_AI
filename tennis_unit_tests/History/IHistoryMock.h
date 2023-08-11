#include "History.h"

class IHistoryMock : public IHistory {

public:
    IHistoryMock() {}
    ~IHistoryMock() {}

    void push( GameState gamestate ) override {} // Mock implementation here

    GameState pop() override { return GameState(); }
    
    int size() override { return 0; }};        