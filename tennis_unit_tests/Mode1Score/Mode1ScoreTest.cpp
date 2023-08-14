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
    std::cout << "TestPlayerPointsEqualOpponentPoints..." << std::endl;
    ON_CALL( mockPlayer1, getPoints()).WillByDefault( testing::Return( 3 ));    // arange
    ON_CALL( mockPlayer2, getPoints()).WillByDefault( testing::Return( 3 ));
    EXPECT_CALL( mockPlayer1, setPoints( 3 )).Times( 1 );           
    EXPECT_CALL( mockPlayer2, setPoints( 3 )).Times( 1 );
    mode1Score->updateScore( &mockPlayer1 );                                    // act            
    std::cout << " finished TestPlayerPointsEqualOpponentPoints." << std::endl;
    ASSERT_EQ( 3, mockPlayer1.getPoints());                                     // assert
    ASSERT_EQ( 3, mockPlayer2.getPoints());           
}

TEST_F( Mode1ScoreTest, TestPlayerWinsGame ) {
    // arrange ( set up initial values )
    EXPECT_CALL( mockPlayer1, getPoints()).Times(testing::AnyNumber()).WillRepeatedly(testing::Return( 5 ));
    EXPECT_CALL( mockPlayer2, getPoints()).Times(testing::AnyNumber()).WillRepeatedly(testing::Return( 3 ));
    
    mode1Score->updateScore( &mockPlayer1 );    // act ( call the method that should change things )

    ASSERT_EQ( 1, mockPlayer1.getGames());      // assert ( changed what it was supposed to? )
    ASSERT_EQ( 0, mockPlayer2.getGames());}


TEST_F(Mode1ScoreTest, TestMode1P1Score_4Points) {
    // Arrange
    ON_CALL(mockPlayer1, getPoints()).WillByDefault(testing::Return(4));
    ON_CALL(mockPlayer2, getPoints()).WillByDefault(testing::Return(2));

    // The exact number of times these methods are called will depend on the
    // implementation of `updateScore`. Adjust the numbers as needed.
    EXPECT_CALL(mockPlayer1, getPoints()).Times(testing::AnyNumber());  // allow any number of calls
    EXPECT_CALL(mockPlayer2, getPoints()).Times(testing::AnyNumber());  // allow any number of calls

    // Act
    mode1Score->updateScore(&mockPlayer1);

    // Assert
    EXPECT_EQ(mockPlayer1.getPoints(), 4);
    EXPECT_EQ(mockPlayer2.getPoints(), 2);
}



// TEST_F( Mode1ScoreTest, TestUpdateServeSwitch) {
//     // Rest of your test case...
// }

// TEST_F( Mode1ScoreTest, TestUpdateSetHistory) {
//     // Rest of your test case...
// }
