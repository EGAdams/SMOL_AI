#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Mode1Score.h"
#include "../History/IHistoryMock.h"
#include "../Player/IPlayerMock.h"
#include "../GameState/IGameStateMock.h"
#include "../PinInterface/IPinInterfaceMock.h"

class Mode1ScoreTest : public ::testing::Test {
protected:
    IPlayerMock mockPlayer1;
    IPlayerMock mockPlayer2; 
    IPinInterfaceMock mockPinInterface; 
    IGameStateMock mockGameState; 
    std::shared_ptr<IHistoryMock> historyMock;
    std::shared_ptr<Mode1Score> mode1Score;
    std::unique_ptr<ScoreBoard> scoreBoard;

    void SetUp() override {
        EXPECT_CALL(mockPlayer1, setOpponent(testing::_)).Times(1);
        EXPECT_CALL(mockPlayer2, setOpponent(testing::_)).Times(1);
        EXPECT_CALL(mockPlayer1, getPoints()).Times(testing::AnyNumber());
        EXPECT_CALL(mockPlayer1, getServe()).Times(testing::AnyNumber()); // Added this line
        EXPECT_CALL(mockPlayer1, number()).Times(testing::AnyNumber());
        EXPECT_CALL(mockPlayer2, getPoints()).Times(testing::AnyNumber());
        EXPECT_CALL(mockPlayer2, getServe()).Times(testing::AnyNumber()); // Added this line
        EXPECT_CALL(mockPlayer2, number()).Times(testing::AnyNumber());
        EXPECT_CALL(mockGameState, getCurrentAction()).Times(testing::AnyNumber());

        mockPlayer1.setOpponent(&mockPlayer2);
        mockPlayer2.setOpponent(&mockPlayer1);

        historyMock = std::make_shared<IHistoryMock>();
        mode1Score  = std::make_shared<Mode1Score>(&mockPlayer1, &mockPlayer2, &mockPinInterface, &mockGameState, historyMock.get());
        scoreBoard  = std::make_unique<ScoreBoard>(&mockPlayer1, &mockPlayer2, &mockGameState);
        mode1Score->setScoreBoard(scoreBoard.get()); 
    }
};

TEST_F(Mode1ScoreTest, TestPlayerPointsEqualOpponentPoints) {
    // Mock expectations and test logic for the scenario where player's points are equal to opponent's points.
}

TEST_F(Mode1ScoreTest, TestPlayerWinsGame) {
    // Mock expectations and test logic for the scenario where the player wins the game.
}

TEST_F(Mode1ScoreTest, TestPlayerReaches4Points) {
    // Mock expectations and test logic for the scenario where the player's points reach 4.
}

TEST_F(Mode1ScoreTest, TestUpdateServeSwitch) {
    // Mock expectations and test logic related to updating the serve switch.
}

TEST_F(Mode1ScoreTest, TestUpdateSetHistory) {
    // Mock expectations and test logic for updating the set history.
}
