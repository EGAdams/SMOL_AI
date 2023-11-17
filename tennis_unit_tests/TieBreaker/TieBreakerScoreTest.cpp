#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../TieBreaker/TieBreaker.h"
#include "../Mode1Score/Mode1Score.h"
#include <iostream>

class TieBreakerScoreTest : public ::testing::Test {
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
 * Test #6 Tiebreak Standard Win - Player 1 wins 7 to 5
 */
// TEST_F(Mode1ScoreTest, Test_Tiebreak_Standard_Win) {
//     printBanner("Test #6\n\nTie Break Standard Win test");
//     setupTieBreak(6, 6);  // Helper function to set both players at 6 games each

//     // Simulate tiebreak where player 1 wins 7 to 5
//     simulateTieBreakPoints(7, 5);  // Helper function to simulate tiebreak points

//     // Verify Player 1 wins the tiebreak
//     ASSERT_EQ(7, player1->getPoints());
//     ASSERT_EQ(5, player2->getPoints());
//     ASSERT_EQ(7, player1->getSetHistory()[1]);
//     ASSERT_EQ(6, player2->getSetHistory()[1]);
//     ASSERT_EQ(false, gameState->getTieBreak());
//     ASSERT_EQ(0, mode1Score->getTieBreaker()->getIteration());

//     printBanner("End of Test #6\n\n");
// }

// /*
//  * Test #7 Tiebreak Win by Two after Max Points - Player 2 wins 15 to 13
//  */
// TEST_F(Mode1ScoreTest, Test_Tiebreak_Win_By_Two_After_Max) {
//     printBanner("Test #7\n\nTie Break Win by Two after Max Points test");
//     setupTieBreak(6, 6);  // Set both players at 6 games each for a tiebreak

//     // Simulate tiebreak where player 2 wins 15 to 13
//     simulateTieBreakPoints(13, 15);  

//     // Verify Player 2 wins the tiebreak
//     ASSERT_EQ(13, player1->getPoints());
//     ASSERT_EQ(15, player2->getPoints());
//     ASSERT_EQ(6, player1->getSetHistory()[1]);
//     ASSERT_EQ(7, player2->getSetHistory()[1]);
//     ASSERT_EQ(false, gameState->getTieBreak());
//     ASSERT_EQ(0, mode1Score->getTieBreaker()->getIteration());

//     printBanner("End of Test #7\n\n");
// }

// /*
//  * Test #8 Tiebreak Scenario - Both players reaching max points without winner
//  */
// TEST_F(Mode1ScoreTest, Test_Tiebreak_Max_Points_No_Winner) {
//     printBanner("Test #8\n\nTie Break Max Points No Winner test");
//     setupTieBreak(6, 6);  // Set both players at 6 games each

//     // Simulate tiebreak where both players reach max points without a winner
//     simulateTieBreakPoints(TIE_BREAK_MAX_POINTS, TIE_BREAK_MAX_POINTS);

//     // Verify no winner has been declared yet
//     ASSERT_EQ(TIE_BREAK_MAX_POINTS, player1->getPoints());
//     ASSERT_EQ(TIE_BREAK_MAX_POINTS, player2->getPoints());
//     ASSERT_EQ(true, gameState->getTieBreak());
//     ASSERT_GT(mode1Score->getTieBreaker()->getIteration(), 0);

//     printBanner("End of Test #8\n\n");
// }

// /*
//  * Test #9 Tiebreak Edge Case - Abnormal Scores
//  */
// TEST_F(Mode1ScoreTest, Test_Tiebreak_Edge_Case_Abnormal_Scores) {
//     printBanner("Test #9\n\nTie Break Edge Case Abnormal Scores test");
//     setupTieBreak(6, 6);  // Set both players at 6 games each

//     // Simulate an edge case scenario with abnormal scores
//     simulateTieBreakPoints(20, 18);  

//     // Verify the game handles this edge case correctly
//     ASSERT_EQ(20, player1->getPoints());
//     ASSERT_EQ(18, player2->getPoints());
//     ASSERT_TRUE(player1->getPoints() > TIE_BREAK_MAX_POINTS && player1->getPoints() - player2->getPoints() >= 2);
//     ASSERT_EQ(7, player1->getSetHistory()[1]);
//     ASSERT_EQ(6, player2->getSetHistory()[1]);
//     ASSERT_EQ(false, gameState->getTieBreak());
//     ASSERT_EQ(0, mode1Score->getTieBreaker()->getIteration());

//     printBanner("End of Test #9\n\n");
// }

// Helper functions setupTieBreak and simulateTieBreakPoints would need to be implemented
// to set the game state appropriately and simulate the scoring of points in a tiebreak.
