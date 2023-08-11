#ifndef IPlayerMock_h
#define IPlayerMock_h
#include <gmock/gmock.h>
#include "IPlayer.h"

class IPlayerMock : public IPlayer
{
public:
    IPlayerMock() {}
    ~IPlayerMock() {}

    MOCK_METHOD(void, setPoints, (int points), (override));
    MOCK_METHOD(int, getPoints, (), (override));
    MOCK_METHOD(void, setOpponent, (IPlayer* opponent), (override));
    MOCK_METHOD(IPlayer*, getOpponent, (), (override));
    MOCK_METHOD(void, setSets, (IGameState* gameState, int sets), (override));
    MOCK_METHOD(int, getSets, (), (override));
    MOCK_METHOD(void, setGames, (int games), (override));
    MOCK_METHOD(int, getGames, (), (override));
    MOCK_METHOD(void, setMatches, (int matches), (override));
    MOCK_METHOD(int, getMatches, (), (override));
    MOCK_METHOD(void, setMode, (int mode), (override));
    MOCK_METHOD(int, getMode, (), (override));
    MOCK_METHOD(void, setSetting, (int setting), (override));
    MOCK_METHOD(int, getSetting, (), (override));
    MOCK_METHOD(int, incrementSetting, (), (override));
    MOCK_METHOD(int, number, (), (override));
    MOCK_METHOD(void, setServeSwitch, (int serve_switch), (override));
    MOCK_METHOD(int, getServeSwitch, (), (override));

    MOCK_METHOD((std::map<int, int>), getSetHistory, (), (override));
    MOCK_METHOD(void, setSetHistory, (int set, int score), (override));
    MOCK_METHOD((std::map<int, int>), getGameHistory, (), (override));
    MOCK_METHOD(void, setGameHistory, (int game, int score), (override));


    
    // Add mock methods for other IPlayer methods as needed
    // For example:
    // MOCK_METHOD(void, setOpponent, (IPlayer* opponent), (override));
    // ... and so on for other methods
};
#endif