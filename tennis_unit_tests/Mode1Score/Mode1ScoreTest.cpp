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

    void SetUp() override {
        std::cout << "Setting up Mode1ScoreTest..." << std::endl;
        IGameState*     gameState = new GameState();
        IPlayer*        player1   = new Player( gameState, PLAYER_1_INITIALIZED );
        IPlayer*        player2   = new Player( gameState, PLAYER_2_INITIALIZED );
        IHistory*       history   = new History();
        std::map< std::string, int > pinMap = {{ "pin", 0 }};
        IPinState*      pinState  = new PinState( pinMap );
        IPinInterface*  pinInterface = new PinInterface( pinState );

        Mode1Score* mode1Score = new Mode1Score( player1, player2, pinInterface, gameState, history );
        ScoreBoard* scoreBoard = new ScoreBoard( player1, player2, gameState );
        mode1Score->setScoreBoard( scoreBoard ); 
    }

    void TearDown() override {
        std::cout << "Tearing down Mode1ScoreTest..." << std::endl;
        delete mode1Score;
        delete scoreBoard;
        delete player1;
        delete player2;
        delete gameState;
        delete history; }
};

TEST_F( Mode1ScoreTest, TestFirstScore ) {   
    std::cout << "make sure player scores are 0" << std::endl;
    ASSERT_EQ( 0, player1->getPoints());
    ASSERT_EQ( 0, player2->getPoints());

    std::cout << "increment player 1 score" << std::endl;
    player1->setPoints( 1 );

    mode1Score->updateScore( player1 );

    ASSERT_EQ( "PLAYER 1: ////// I 15 //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: ////// I 00 //////", scoreBoard->drawPlayerScore( player2 ));
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

TEST_F(Mode1ScoreTest, TestMode1P1Score_4Points) {
    // Arrange
    player1->setPoints( 4 );
    player2->setPoints( 2 );


    // Act
    mode1Score->updateScore( player1 );

    // Assert
    EXPECT_EQ( player1->getPoints(), 4);
    EXPECT_EQ( player2->getPoints(), 2);
}