#include <gtest/gtest.h>
#include "Mode1Score.h"
#include "../Player/IPlayerMock.cpp" // Assume we have a mock for IPlayer
#include "GameStateMock.h" // Assume we have a mock for GameState
#include "HistoryMock.h" // Assume we have a mock for History

class Mode1ScoreTest : public testing::Test {
protected:
    IPlayerMock* player1;
    IPlayerMock* player2;
    PinInterfaceMock* pinInterface; // Assume we have a mock for PinInterface
    GameStateMock* gameState;
    HistoryMock* history;
    Mode1Score* mode1Score;

    void SetUp() override {
        player1 = new IPlayerMock();
        player2 = new IPlayerMock();
        pinInterface = new PinInterfaceMock();
        gameState = new GameStateMock();
        history = new HistoryMock();
        mode1Score = new Mode1Score(player1, player2, pinInterface, gameState, history);
    }

    void TearDown() override {
        delete mode1Score;
        delete history;
        delete gameState;
        delete pinInterface;
        delete player2;
        delete player1;
    }
};

TEST_F(Mode1ScoreTest, UpdateScoreIncreasesPlayerScore) {
    EXPECT_CALL(*player1, getPoints()).WillOnce(testing::Return(2));
    EXPECT_CALL(*player1, setPoints(3));
    
    mode1Score->updateScore(player1);
}
