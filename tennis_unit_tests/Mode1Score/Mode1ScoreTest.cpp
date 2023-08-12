#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Mode1Score.h"
#include "../History/IHistoryMock.h"
#include "../Player/IPlayerMock.h"
#include "../GameState/IGameStateMock.h"
#include "../PinInterface/IPinInterfaceMock.h"

class Mode1ScoreTest : public ::testing::Test
{
protected:
    IPlayerMock mockPlayer1;             // Move the mock objects to class members
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
        ON_CALL( mockPlayer1, getServe()).WillByDefault(  testing::Return( 0 ));
        ON_CALL( mockPlayer1, setOpponent( testing::_ )).WillByDefault( testing::Return());
        ON_CALL( mockPlayer1, getPoints()).WillByDefault( testing::Return( 0 ));
        ON_CALL( mockPlayer1, getServe()).WillByDefault( testing::Return( 0 ));
        ON_CALL( mockPlayer1, number()).WillByDefault( testing::Return( 0 ));
        
        ON_CALL( mockPlayer2, getPoints()).WillByDefault( testing::Return( 0 ));
        ON_CALL( mockPlayer2, getServe()).WillByDefault(  testing::Return( 0 ));
        ON_CALL( mockPlayer2, setOpponent( testing::_ )).WillByDefault( testing::Return());
        ON_CALL( mockPlayer2, getPoints()).WillByDefault( testing::Return( 0 ));
        ON_CALL( mockPlayer2, getServe()).WillByDefault( testing::Return( 0 ));
        ON_CALL( mockPlayer2, number()).WillByDefault( testing::Return( 0 ));

        ON_CALL(mockGameState, getCurrentAction()).WillByDefault( testing::Return( "" ));

        historyMock = std::make_shared<IHistoryMock>();
        mode1Score  = std::make_shared<Mode1Score>( &mockPlayer1, &mockPlayer2, &mockPinInterface, &mockGameState, historyMock.get());
        scoreBoard  = std::make_unique<ScoreBoard>(&mockPlayer1, &mockPlayer2, &mockGameState);
        mode1Score->setScoreBoard( scoreBoard.get()); 
    }
};


int main( int argc, char** argv ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}


TEST_F( Mode1ScoreTest, UpdateScoreIncreasesPlayerScore ) {
    EXPECT_CALL(mockPlayer1, getPoints()).Times( testing::AnyNumber()).WillRepeatedly( testing::Return( 0 ));
    EXPECT_CALL(mockPlayer1, getPoints()).WillOnce( testing::Return( 2 ));
    EXPECT_CALL(mockPlayer1, setPoints( 3 ));
    mode1Score->updateScore( &mockPlayer1 );
    std::cout << "mockPlayer1.getPoints(): " << mockPlayer1.getPoints() << std::endl;
    EXPECT_EQ( 2, mockPlayer1.getPoints());
}

TEST_F(Mode1ScoreTest, TestCalculateScore)
{
    // Replace this with your actual test
    // Here's an example:
    // EXPECT_EQ(mode1Score->calculateScore(), expectedScore);
}

// TEST_F(Mode1ScoreTest, TestUpdateScore) {
//     IPlayerMock mockPlayer; // Create a mock player  
//     EXPECT_CALL(mockPlayer, getHistory()).Times(1); // Set expectations on the mock player
//     mode1Score->updateScore(&mockPlayer); } // Call the method under test