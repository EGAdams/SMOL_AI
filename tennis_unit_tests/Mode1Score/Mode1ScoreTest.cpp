#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Mode1Score.h"
#include "../History/History.h"
#include "../Player/Player.h"

class Mode1ScoreTest : public ::testing::Test {
protected:
    PinInterface* inInterface; 
    History* history;
    Mode1Score* mode1Score;
    ScoreBoard* scoreBoard;
    Player* player1;
    Player* player2;
    GameState* gameState;
    PinInterface* pinInterface;
    PinState* pinState;
    std::map< std::string, int > pin_map;

    void printBanner( std::string text_to_print ) {
        std::cout << "\n\n\n\n\n\n" << std::endl;
        std::cout << "==============================================" << std::endl;
        std::cout << text_to_print << std::endl;
        std::cout << "==============================================" << std::endl;
    }

    void SetUp() override {
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
    player1->setPoints( 1 );

    mode1Score->updateScore( player1 );

    ASSERT_EQ( "PLAYER 1: ////// I 15 //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   00 //////", scoreBoard->drawPlayerScore( player2 ));
}


TEST_F( Mode1ScoreTest, TestPlayerPointsEqualOpponentPoints) {
    std::cout << "TestPlayerPointsEqualOpponentPoints..." << std::endl;
    player1->setPoints( 3 );
    player2->setPoints( 3 );
    mode1Score->updateScore( player1 );                                          
    ASSERT_EQ( 3, player1->getPoints());
    ASSERT_EQ( 3, player2->getPoints());           
    std::cout << " finished TestPlayerPointsEqualOpponentPoints." << std::endl;
}

TEST_F( Mode1ScoreTest, TestPlayerWinsGame ) {
    player1->setPoints( 5 );
    player2->setPoints( 3 );
    mode1Score->updateScore( player1 );    
    ASSERT_EQ( 1, player1->getGames());     // player 1 wins game    
    ASSERT_EQ( 0, player2->getGames()); }

TEST_F( Mode1ScoreTest, TestMode1P1Score_3Points) {
    player1->setPoints( 3 );                        // Arrange
    player2->setPoints( 2 );   
    mode1Score->updateScore( player1 );             // Act
    EXPECT_EQ( player1->getPoints(), 3);
    EXPECT_EQ( player2->getPoints(), 2 );           // Assert
    ASSERT_EQ( "PLAYER 1: ////// I 40 //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   30 //////", scoreBoard->drawPlayerScore( player2 ));
}

TEST_F( Mode1ScoreTest, TestDeuceScenario ) {
    ASSERT_EQ( 0, player1->getPoints()); // Ensure both players start with 0 points
    ASSERT_EQ( 0, player2->getPoints());

    for ( int i = 0; i < 3; i++ ) { // Update scores such that both players reach 40 ( i.e., 3 points)
        player1->setPoints( i + 1 );
        player2->setPoints( i + 1 );
        mode1Score->updateScore( player1 );
        mode1Score->updateScore( player2 ); }

    ASSERT_EQ( 3, player1->getPoints());
    ASSERT_EQ( 3, player2->getPoints()); // At this point, the score should be "deuce"
    ASSERT_EQ( "PLAYER 1: ////// I 40 //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   40 //////", scoreBoard->drawPlayerScore( player2 ));
   
    player1->setPoints(   4 ); // Update score such that player1 gains advantage
    mode1Score->updateScore( player1 );
    ASSERT_EQ( "PLAYER 1: ////// I Ad //////", scoreBoard->drawPlayerScore( player1 )); // Verify that player1 has the advantage
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

    for ( int i = 0; i < 3; i++ ) { // Update scores to reach deuce
        player1->setPoints( i + 1 );
        player2->setPoints( i + 1 );
        mode1Score->updateScore( player1 );
        mode1Score->updateScore( player2 ); }

    ASSERT_EQ( 3, player1->getPoints());
    ASSERT_EQ( 3, player2->getPoints());
   
    player1->setPoints( 4 );
    mode1Score->updateScore( player1 ); // Player1 gains advantage
    ASSERT_EQ( "PLAYER 1: ////// I Ad //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   40 //////", scoreBoard->drawPlayerScore( player2 ));
    
    player1->setPoints( 5 );            // Player1 wins the game after advantage
    mode1Score->updateScore( player1 ); // Verify that player1 has won the game
   
    ASSERT_EQ( 1, player1->getGames()); // player 1 wins game    
    ASSERT_EQ( 0, player2->getGames());
}

/*
 * Test #4: The Dreaded Tie Break Scenario
 * Includes server logic testing
*/
TEST_F( Mode1ScoreTest, TestTiebreakScenarios ) {
    printBanner( "Test #4\n\nTie Break Scenario test" );
    player1->setGames(  5 ); // Mock a situation where both players have 
    player2->setGames(  6 ); // 6 games each in a set, leading to a tiebreak
    ASSERT_EQ( 5, player1->getGames()); // Verify that we are setting up a tiebreak 
    ASSERT_EQ( 6, player2->getGames()); // for when player 1 wins the next game

    player1->setPoints( 4 );
    player2->setPoints( 3 );
    ASSERT_EQ( 4, player1->getPoints()); // Verify player 1 is one point away from winning the game
    ASSERT_EQ( 3, player2->getPoints());

    player1->setPoints( 5 ); // This game score should set up for a tie break trigger
    mode1Score->updateScore( player1 ); // This game win should trigger the tie break

    std::cout << "checking tiebreak flag... " << std::endl;
    std::cout << "tiebreak flag: " << gameState->getTieBreak() << std::endl;
    ASSERT_EQ( true, gameState->getTieBreak()); // ASSERT tie break flag is true

    // make sure that player 1 is the server
    ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());

    std::cout << "simulating the progression of points during the tiebreak... " << std::endl;
    for ( int i = 0; i < 8; i++ ) {
        gameState->setPlayerButton( PLAYER_ONE_BUTTON );
        player1->setPoints( i + 1 );
        mode1Score->updateScore( player1 );

        // after the first score, player 2 is the server for the next 2 points
        if ( i == 0 ) {        ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 1 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 2 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 3 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 4 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 5 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 6 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 7 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe()); }

        gameState->setPlayerButton( PLAYER_TWO_BUTTON );
        player2->setPoints( i + 1 );
        mode1Score->updateScore( player2 );

        if ( i == 0 ) {        ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 1 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 2 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 3 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 4 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 5 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 6 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 7 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe()); }
    }
    // At this point, the score should be "eight all"
    ASSERT_EQ( 8, player1->getPoints());
    ASSERT_EQ( 8, player2->getPoints());

    // Player1 scores the next point
    player1->setPoints( 9 );
    mode1Score->updateScore( player1 );
    
    // Verify that the tiebreak hasn't been won yet since there isn't a 2 point lead
    ASSERT_EQ( 9, player1->getPoints());
    ASSERT_EQ( 8, player2->getPoints());
    ASSERT_EQ( 6, player1->getGames());
    ASSERT_EQ( 6, player2->getGames());
    ASSERT_EQ( true, gameState->getTieBreak()); // ASSERT tie break flag is true

    // Player1 scores one more point and wins the tiebreak
    player1->setPoints(           10 );
    mode1Score->updateScore( player1 );
    
    // Verify that player1 has won the tiebreak and the set
    ASSERT_EQ( 7, player1->getSetHistory()[ 1 ]);
    ASSERT_EQ( 6, player2->getSetHistory()[ 1 ]);

    // Verify that the tiebreak flag is false
    ASSERT_EQ( false, gameState->getTieBreak()); // ASSERT tie break flag is false
    
    // verify that the tie break iteration is 0
    ASSERT_EQ( 0, mode1Score->getTieBreaker()->getIteration()); // ASSERT tie break iteration is 0

    printBanner( "End of Test #4\n\n" );
}


/*
 * Test #5 Tiebreak Scenario 2 - Player 1 wins 13 to 12
 */
TEST_F( Mode1ScoreTest, Test_Tiebreak_13_by_one ) {
    printBanner( "Test #5\n\nTie Break Scenario 13 by 1 test" );
    player1->setGames( 5 ); // Mock a situation where both players have 
    player2->setGames( 6 ); // 6 games each in a set, leading to a tiebreak
    ASSERT_EQ( 5, player1->getGames() ); // Verify that we are setting up a tiebreak 
    ASSERT_EQ( 6, player2->getGames() ); // for when player 1 wins the next game

    player1->setPoints( 4 );
    player2->setPoints( 3 );
    ASSERT_EQ( 4, player1->getPoints() ); // Verify player 1 is one point away from winning the game
    ASSERT_EQ( 3, player2->getPoints() );

    player1->setPoints( 5 ); // This game score should set up for a tie break trigger
    mode1Score->updateScore( player1 ); // This game win should trigger the tie break

    std::cout << "checking tiebreak flag... " << std::endl;
    std::cout << "tiebreak flag: " << gameState->getTieBreak() << std::endl;
    ASSERT_EQ( true, gameState->getTieBreak() ); // ASSERT tie break flag is true

    // make sure that player 1 is the server
    ASSERT_EQ( PLAYER_1_SERVE, gameState->getServe() );

    std::cout << "simulating the progression of points during the tiebreak... " << std::endl;
    for ( int i = 0; i < 12; i++ ) {
        gameState->setPlayerButton( PLAYER_ONE_BUTTON );
        player1->setPoints( i + 1 );
        mode1Score->updateScore( player1 );

        if ( i == 0 ) {         ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 1  ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 2  ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 3  ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 4  ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 5  ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 6  ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 7  ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 8  ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 9  ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 10 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 11 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe()); }

        gameState->setPlayerButton( PLAYER_TWO_BUTTON );
        player2->setPoints( i + 1 );
        mode1Score->updateScore( player2 );

        if ( i == 0 ) {         ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 1  ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 2  ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 3  ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 4  ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 5  ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 6  ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 7  ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 8  ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 9  ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 10 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 11 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe()); }
    }

    // At this point, the score should be "twelve all"
    ASSERT_EQ( 12, player1->getPoints() );
    ASSERT_EQ( 12, player2->getPoints() );

    // Player1 scores the next point to win the tiebreak
    player1->setPoints( 13 );
    mode1Score->updateScore( player1 ); // for the win...
    
    // Verify that player1 has won the tiebreak and the set
    ASSERT_EQ( 7, player1->getSetHistory()[ 1 ] );
    ASSERT_EQ( 6, player2->getSetHistory()[ 1 ] );

    // Verify that the tiebreak flag is false
    ASSERT_EQ( false, gameState->getTieBreak() ); // ASSERT tie break flag is false
    
    // verify that the tie break iteration is 0
    ASSERT_EQ( 0, mode1Score->getTieBreaker()->getIteration() ); // ASSERT tie break iteration is 0

    printBanner( "End of Test #5\n\n" );
}



/*
 * Test #6 Player 1 wins a set, Player 2 wins a set, Player 1 wins a set and therefore the match
 */
TEST_F( Mode1ScoreTest, Test_Two_Set_Win_Scenario ) {
    printBanner( "Test #6\n\nTwo Set Match win scenario test" );
    
    // make sure Player One and Player Two have 0 points to start
    ASSERT_EQ( 0, player1->getPoints());
    ASSERT_EQ( 0, player2->getPoints());

    // verify that the set is 1
    ASSERT_EQ( 1, gameState->getCurrentSet() );

    // Set 1: Player 1 wins
    player1->setGames(  5 ); // Player One has 5 games
    player2->setGames(  4 ); // Player Two has 4 games
    player1->setPoints( 4 ); // Player 1 wins the next game ( 4 to 0 ) to win Set 1
    mode1Score->updateScore( player1 );

    ASSERT_EQ( 6, player1->getSetHistory()[ 1 ] ); // make sure that the set
    ASSERT_EQ( 4, player2->getSetHistory()[ 1 ] ); // history is good at this point

    // make sure that the set is "2"
    ASSERT_EQ( 2, gameState->getCurrentSet() );

    // make sure Player One and Player Two have 0 points to start
    ASSERT_EQ( 0, player1->getPoints());
    ASSERT_EQ( 0, player2->getPoints());
    
    // Set 2: Player 1 wins match
    player1->setGames(  5 ); // Player One has 5 games
    player2->setGames(  4 ); // Player Two has 4 games
    player1->setPoints( 4 ); // Player 1 wins the next game to win Set 2
    mode1Score->updateScore( player1 );

    // This should be a match win, thy game should be over
    ASSERT_EQ( 0, gameState->gameRunning());

    printBanner( "End of Modified Test Case\n\n" );
}


