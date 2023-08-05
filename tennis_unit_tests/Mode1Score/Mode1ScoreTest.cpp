#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Mode1Score.h"



class Mode1ScoreTest : public ::testing::Test {
protected:
    GameState gameState;
    Player player1{&gameState, 1}, player2{&gameState, 2};
    std::map<std::string, int> pinMap; // You may need to populate this map as necessary
    PinState pinState{pinMap};
    PinInterface pinInterface{&pinState};
    History history;
    Mode1Score* mode1Score;

    Mode1ScoreTest() {
        mode1Score = new Mode1Score( &player1, &player2, &pinInterface, &gameState, &history );
    }

    void TearDown() override {
        delete mode1Score;
    }
};




TEST_F(Mode1ScoreTest, Mode1P1ScoreTest) {
    // Now you can use player1, player2, pinInterface, gameState, and history

    // Set player 1 score to 2
    player1.setPoints( 2 );

    // Call the mode1P1Score method
    mode1Score->mode1P1Score();

    // Check that the score has been updated correctly
    ASSERT_EQ(player1.getPoints(), 3 );
}