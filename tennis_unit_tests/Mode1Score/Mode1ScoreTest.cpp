#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Mode1Score.h"
#include "../History/IHistoryMock.h"
#include "../Player/IPlayerMock.h"
#include "../GameState/IGameStateMock.h"
#include "../PinInterface/IPinInterfaceMock.h"

class Mode1ScoreTest : public ::testing::Test {
protected:
    IPinInterface* inInterface; 
    IHistory* history;
    Mode1Score* mode1Score;
    ScoreBoard* scoreBoard;
    IPlayer* player1;
    IPlayer* player2;
    IGameState* gameState;
    IPinInterface* pinInterface;
    IPinState* pinState;
    std::map< std::string, int > pin_map;

    void SetUp() override {
        // std::cout << "Setting up Mode1ScoreTest..." << std::endl;
        gameState = new GameState();
        player1 = new Player( gameState, PLAYER_1_INITIALIZED );
        player2 = new Player( gameState, PLAYER_2_INITIALIZED ); 
        player1->setOpponent( player2 ); player2->setOpponent( player1 );
        history = new History();
        pin_map = {{ "pin", 0 }};
        pinState = new PinState( pin_map );
        pinInterface = new PinInterface( pinState );

        mode1Score = new Mode1Score( player1, player2, pinInterface, gameState, history );
        scoreBoard = new ScoreBoard( player1, player2, gameState );
        mode1Score->setScoreBoard( scoreBoard ); 
    }

    void TearDown() override {
        // std::cout << "Tearing down Mode1ScoreTest..." << std::endl;
        delete mode1Score;
        delete scoreBoard;
        delete player1;
        delete player2;
        delete gameState;
        delete history; 
        delete pinInterface;
        delete pinState; 
        std::cout << "\n\n" << std::endl;
        }
};

TEST_F( Mode1ScoreTest, TestFirstScore ) {   
    std::cout << "make sure player scores are 0" << std::endl;
    ASSERT_EQ( 0, player1->getPoints());
    ASSERT_EQ( 0, player2->getPoints());

    std::cout << "increment player 1 score" << std::endl;
    player1->setPoints(   1 );

    mode1Score->updateScore( player1 );

    ASSERT_EQ( "PLAYER 1: ////// I 15 //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   00 //////", scoreBoard->drawPlayerScore( player2 ));
}


TEST_F( Mode1ScoreTest, TestPlayerPointsEqualOpponentPoints) {
    std::cout << "TestPlayerPointsEqualOpponentPoints..." << std::endl;
    player1->setPoints(   3 );
    player2->setPoints(   3 );
    mode1Score->updateScore( player1 );                                          
    ASSERT_EQ( 3, player1->getPoints());
    ASSERT_EQ( 3, player2->getPoints());           
    std::cout << " finished TestPlayerPointsEqualOpponentPoints." << std::endl;
}

TEST_F( Mode1ScoreTest, TestPlayerWinsGame ) {
    player1->setPoints(   5 );
    player2->setPoints(   3 );
    mode1Score->updateScore( player1 );    
    ASSERT_EQ( 1, player1->getGames());     // player 1 wins game    
    ASSERT_EQ( 0, player2->getGames()); }

TEST_F(Mode1ScoreTest, TestMode1P1Score_3Points) {
    player1->setPoints(   3 );                        // Arrange
    player2->setPoints(   2 );   
    mode1Score->updateScore( player1 );             // Act
    EXPECT_EQ( player1->getPoints(), 3);
    EXPECT_EQ( player2->getPoints(), 2);            // Assert
    ASSERT_EQ( "PLAYER 1: ////// I 40 //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   30 //////", scoreBoard->drawPlayerScore( player2 ));
}

TEST_F( Mode1ScoreTest, TestDeuceScenario ) {
    ASSERT_EQ( 0, player1->getPoints()); // Ensure both players start with 0 points
    ASSERT_EQ( 0, player2->getPoints());

    for ( int i = 0; i < 3; i++ ) { // Update scores such that both players reach 40 (i.e., 3 points)
        player1->setPoints( i + 1 );
        player2->setPoints( i + 1 );
        mode1Score->updateScore( player1 );
        mode1Score->updateScore( player2 ); }

    ASSERT_EQ( 3, player1->getPoints());
    ASSERT_EQ( 3, player2->getPoints()); // At this point, the score should be "deuce"
    ASSERT_EQ( "PLAYER 1: ////// I 40 //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   40 //////", scoreBoard->drawPlayerScore( player2 ));
   
    player1->setPoints(   4 ); // Update score such that player1 gains advantage
    mode1Score->updateScore( player1 ); // Verify that player1 has the advantage
    ASSERT_EQ( "PLAYER 1: ////// I Ad //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   40 //////", scoreBoard->drawPlayerScore( player2 ));
    player2->setPoints(   4 ); // Update score such that player2 ties the score, returning to deuce
    mode1Score->updateScore( player2 ); // Verify the score is deuce again
    ASSERT_EQ( "PLAYER 1: ////// I 40 //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   40 //////", scoreBoard->drawPlayerScore( player2 ));
}

TEST_F( Mode1ScoreTest, TestWinAfterAdvantage ) {
    // Ensure both players start with 0 points
    ASSERT_EQ( 0, player1->getPoints());
    ASSERT_EQ( 0, player2->getPoints());

    // Update scores to reach deuce
    for ( int i = 0; i < 3; i++ ) {
        player1->setPoints( i + 1 );
        player2->setPoints( i + 1 );
        mode1Score->updateScore( player1 );
        mode1Score->updateScore( player2 );
    }
    ASSERT_EQ(3, player1->getPoints());
    ASSERT_EQ(3, player2->getPoints());

    // Player1 gains advantage
    player1->setPoints( 4 );
    mode1Score->updateScore( player1 );
    ASSERT_EQ( "PLAYER 1: ////// I Ad //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   40 //////", scoreBoard->drawPlayerScore( player2 ));
    
    // Player1 wins the game after advantage
    player1->setPoints( 5 );
    mode1Score->updateScore( player1 ); // Verify that player1 has won the game
   
    ASSERT_EQ( 1, player1->getGames());     // player 1 wins game    
    ASSERT_EQ( 0, player2->getGames());
}

// TEST_F( Mode1ScoreTest, TestTiebreakScenarios ) {
//     // Mock a situation where both players have 6 games each in a set, leading to a tiebreak
//     // ... [This might involve some additional mocking based on the implementation details]
    
//     // Simulate the progression of points in the tiebreak
//     for (int i = 0; i < 6; i++) {
//         player1->setPoints(i + 1);
//         player2->setPoints(i + 1);
//         mode1Score->updateScore(player1);
//         mode1Score->updateScore(player2);
//     }
//     // At this point, the score should be "six all"

//     // Player1 scores the next point and wins the tiebreak
//     player1->setPoints(7);
//     mode1Score->updateScore(player1);
//     // Verify that player1 has won the tiebreak
// }

