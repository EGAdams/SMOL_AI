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
        mockPlayer1.setOpponent( &mockPlayer2 );
        mockPlayer2.setOpponent( &mockPlayer1 );

        // Add the ON_CALL statements here
        ON_CALL( mockPlayer1, getPoints()).WillByDefault( testing::Return( 0 ));
        ON_CALL( mockPlayer1, getServe()).WillByDefault( testing::Return( 0 ));
        ON_CALL( mockPlayer1, setOpponent( testing::_ )).WillByDefault( testing::Return());
        ON_CALL( mockPlayer1, number()).WillByDefault( testing::Return( 0 ));

        ON_CALL( mockPlayer2, getPoints()).WillByDefault( testing::Return( 0 ));
        ON_CALL( mockPlayer2, getServe()).WillByDefault( testing::Return( 0 ));
        ON_CALL( mockPlayer2, setOpponent( testing::_ )).WillByDefault( testing::Return());
        ON_CALL( mockPlayer2, number()).WillByDefault( testing::Return( 0 ));

        ON_CALL(mockGameState, getCurrentAction()).WillByDefault( testing::Return( "" ));

        // Setting expectations
        EXPECT_CALL(mockPlayer1, getServe()).Times(testing::AnyNumber());
        EXPECT_CALL(mockPlayer2, getServe()).Times(testing::AnyNumber());

        historyMock = std::make_shared<IHistoryMock>();
        mode1Score  = std::make_shared<Mode1Score>( &mockPlayer1, &mockPlayer2, &mockPinInterface, &mockGameState, historyMock.get());
        scoreBoard  = std::make_unique<ScoreBoard>(&mockPlayer1, &mockPlayer2, &mockGameState);
        mode1Score->setScoreBoard( scoreBoard.get()); 
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
