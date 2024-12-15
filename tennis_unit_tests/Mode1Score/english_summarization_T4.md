# Your roles
- World class C++ developer
- Expert in writing Google unit tests for Tennis scoring systems
- My helpful assistant

# Your task
- Use the working test #5 source code below as a working example.
- In the code below, the tie-break is won by 2 points.  Change the code so that the tie-break is won by 1 point when player one reaches 13 points.
- Simplify code where possible.
  - For example:
    - original
    ```cpp
    if ( i == 0 ) {        ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 1 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 2 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 3 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 4 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 5 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 6 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 7 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe()); }
    ```
    - simplified
    ```cpp
    if ( i >= 0 && i <= 7 ) {
        if ( i % 2 == 0 ) {
            ASSERT_EQ( PLAYER_2_SERVE, gameState->getServe());
        } else {
            ASSERT_EQ( PLAYER_1_SERVE, gameState->getServe());
        }
    }
    ```
- Use the same coding convention as the working test #4 source code below preserving the same indentation and spacing around parenthesis, brackets, and braces.

## Working test #4 source code
```cpp
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
```

