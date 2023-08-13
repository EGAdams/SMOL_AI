#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Mode1Score.h"
#include "../History/IHistoryMock.h"
#include "../Player/IPlayerMock.h"
#include "../GameState/IGameStateMock.h"
#include "../PinInterface/IPinInterfaceMock.h"

class Mode1ScoreTest : public ::testing::Test {
protected:
    testing::NiceMock< IPlayerMock > mockPlayer1;
    testing::NiceMock< IPlayerMock > mockPlayer2; 
    testing::NiceMock< IPinInterfaceMock > mockPinInterface; 
    testing::NiceMock< IGameStateMock > mockGameState; 
    std::shared_ptr< IHistoryMock > historyMock;
    std::shared_ptr< Mode1Score > mode1Score;
    std::unique_ptr< ScoreBoard> scoreBoard;

    void SetUp() override {
        std::cout << "Setting up Mode1ScoreTest..." << std::endl;
        ON_CALL( mockPlayer1, setOpponent( &mockPlayer2 )).WillByDefault( testing::Return());
        ON_CALL( mockPlayer1, getOpponent()).WillByDefault( testing::Return( &mockPlayer2 ));
        ON_CALL( mockPlayer2, setOpponent( &mockPlayer1 )).WillByDefault( testing::Return());
        ON_CALL( mockPlayer2, getOpponent()).WillByDefault( testing::Return( &mockPlayer1 ));

        historyMock = std::make_shared< IHistoryMock >();
        mode1Score  = std::make_shared< Mode1Score >( &mockPlayer1, &mockPlayer2, &mockPinInterface, &mockGameState, historyMock.get());
        scoreBoard  = std::make_unique< ScoreBoard >( &mockPlayer1, &mockPlayer2, &mockGameState );
        mode1Score->setScoreBoard( scoreBoard.get()); 
    }
};

TEST_F( Mode1ScoreTest, TestPlayerPointsEqualOpponentPoints) {
    std::cout << "Constructing Mode1Score..." << std::endl;
    // Mode1Score mode1Score( &mockPlayer1, &mockPlayer2, &mockPinInterface, &mockGameState, historyMock.get());

    // Set up the initial scenario using the mock players
    ON_CALL( mockPlayer1, getPoints()).WillByDefault( testing::Return( 3 ));
    ON_CALL( mockPlayer2, getPoints()).WillByDefault( testing::Return( 3 ));

    EXPECT_CALL( mockPlayer1, setPoints( 3 )).Times( 1 );
    EXPECT_CALL( mockPlayer2, setPoints( 3 )).Times( 1 );

    std::cout << "Mock player1 points: " << mockPlayer1.getPoints() << std::endl;
    std::cout << "Mock player2 points: " << mockPlayer2.getPoints() << std::endl;

    std::cout << "About to call mode1Score.updateScore() in test..." << std::endl;
    mode1Score->updateScore( &mockPlayer1 );
}

TEST_F( Mode1ScoreTest, TestPlayerWinsGame ) {
    // Mock expectations and test logic for the scenario where 
    // player's points are equal to opponent's points.

    // ON_CALL( mockPlayer1, getServe()).WillByDefault( testing::Return( 0 ));
    // ON_CALL( mockPlayer2, getServe()).WillByDefault( testing::Return( 0 ));
    // ON_CALL( mockGameState, getServe()).WillByDefault(testing::Return( 0 ));
    
    // // Specify the expectation for the getServe() method
    // EXPECT_CALL( mockPlayer1, getServe()).Times( testing::AnyNumber());
    // EXPECT_CALL( mockPlayer2, getServe()).Times( testing::AnyNumber());
    // EXPECT_CALL( mockGameState, getServe()).Times( testing::AnyNumber());

    // Rest of your test case...
}

TEST_F( Mode1ScoreTest, TestPlayerReaches4Points) {
    // Mock expectations and test logic for the scenario where the player's points reach 4.
    // Mock expectations and test logic for the scenario where 
    // player's points are equal to opponent's points.

    // ON_CALL( mockPlayer1, getServe()).WillByDefault( testing::Return( 0 ));
    // ON_CALL( mockPlayer2, getServe()).WillByDefault( testing::Return( 0 ));
    // ON_CALL( mockGameState, getServe()).WillByDefault(testing::Return( 0 ));
    
    // // Specify the expectation for the getServe() method
    // EXPECT_CALL( mockPlayer1, getServe()).Times( testing::AnyNumber());
    // EXPECT_CALL( mockPlayer2, getServe()).Times( testing::AnyNumber());
    // EXPECT_CALL( mockGameState, getServe()).Times( testing::AnyNumber());

    // Rest of your test case...
}

TEST_F( Mode1ScoreTest, TestUpdateServeSwitch) {
    // Mock expectations and test logic related to updating the serve switch.
    // Mock expectations and test logic for the scenario where 
    // player's points are equal to opponent's points.

    // ON_CALL( mockPlayer1, getServe()).WillByDefault( testing::Return( 0 ));
    // ON_CALL( mockPlayer2, getServe()).WillByDefault( testing::Return( 0 ));
    // ON_CALL( mockGameState, getServe()).WillByDefault(testing::Return( 0 ));
    
    // // Specify the expectation for the getServe() method
    // EXPECT_CALL( mockPlayer1, getServe()).Times( testing::AnyNumber());
    // EXPECT_CALL( mockPlayer2, getServe()).Times( testing::AnyNumber());
    // EXPECT_CALL( mockGameState, getServe()).Times( testing::AnyNumber());

    // Rest of your test case...
}

TEST_F( Mode1ScoreTest, TestUpdateSetHistory) {
    // Mock expectations and test logic for updating the set history.
    // Mock expectations and test logic for the scenario where 
    // player's points are equal to opponent's points.

    // ON_CALL( mockPlayer1, getServe()).WillByDefault( testing::Return( 0 ));
    // ON_CALL( mockPlayer2, getServe()).WillByDefault( testing::Return( 0 ));
    // ON_CALL( mockGameState, getServe()).WillByDefault(testing::Return( 0 ));
    
    // // Specify the expectation for the getServe() method
    // EXPECT_CALL( mockPlayer1, getServe()).Times( testing::AnyNumber());
    // EXPECT_CALL( mockPlayer2, getServe()).Times( testing::AnyNumber());
    // EXPECT_CALL( mockGameState, getServe()).Times( testing::AnyNumber());

    // Rest of your test case...
}
