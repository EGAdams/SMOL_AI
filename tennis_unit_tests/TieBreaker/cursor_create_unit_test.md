# Your roles
- World class C++ developer
- Expert in writing Google unit tests for Tennis scoring systems

# Your task
- Use the working Mode1ScoreTest class source code below as a working example.
- Create a comprehensive set of unit tests for the TieBreaker class.
- Use the same coding convention as the working test #5 source code below preserving the same indentation and spacing around parenthesis, brackets, and braces.

## Working test #5 source code
```cpp
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
```