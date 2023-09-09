# Your Roles
	- Expert C++ Developer
	- My excellent teacher
	- My helpful assistant

# Your Task
    - Use the following source code to analyze all of the steps that build up to test_03.
    - Keep in mind that we will be writing a unit test for test_03.

```cpp
#include "../include/led-matrix.h"
#include "../include/graphics.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <csignal>
#include <map>
#include "FontLoader/FontLoader.h"
#include "TextDrawer/TextDrawer.h"
#include "NumberDrawer/NumberDrawer.h"
#include "ScoreBoard/ScoreBoard.h"
#include "GameObject/GameObject.h"

using namespace rgb_matrix;
#define SCORE_DELAY    .15
#define MAX_LOOP_COUNT 350
#define A_SPACE        13
#define FOUR_SPACE     14
#define THREE_SPACE    15

void writeMessage( GameObject* gameObject, std::string message ) {
    std::cout << "writing message: " << message << std::endl;
    gameObject->getScoreBoard()->clearScreen();
    gameObject->getScoreBoard()->writeMessage( message );
    gameObject->getScoreBoard()->clearScreen();
    std::cout << "done writing message." << std::endl; }

void score( GameObject* gameObject, GameState* gameState, int player ) {
    std::cout << "\n\n\n\n\n\n\n*** Player " << player << " scored ***\n" << std::endl;
    gameObject->playerScore( player );  // flip the player score flag
    gameObject->loopGame();  // handle the player score flag
    std::cout << "player 1 points: " << gameState->getPlayer1Points();
    std::cout << "player 2 points: " << gameState->getPlayer2Points() << std::endl;
    std::cout << "player 1 games:  " << gameState->getPlayer1Games();
    std::cout << "player 2 games:  " << gameState->getPlayer2Games() << std::endl;
    std::cout << "player 1 sets:   " << gameState->getPlayer1Sets();
    std::cout << "player 2 sets:   " << gameState->getPlayer2Sets();
    std::cout << "current set:     " << gameState->getCurrentSet() << std::endl;
    std::map<int, int> _player1_set_history = gameState->getPlayer1SetHistory();
    std::map<int, int> _player2_set_history = gameState->getPlayer2SetHistory(); }

void playerWin( GameObject* gameObject, GameState* gameState, int player ) {
    score( gameObject, gameState, player );
    score( gameObject, gameState, player );
    score( gameObject, gameState, player );
    score( gameObject, gameState, player ); }

void test_01( GameObject* gameObject, GameState* gameState, int* loop_count ) {
    std::signal( SIGINT, GameObject::_signalHandler );
    gameObject->getScoreBoard()->clearScreen();
    std::cout << "done sleeping.  calling gameObject->getScoreBoard()->writeMessage(). calling loopGame()..." << std::endl;
    std::cout << "calling game object start()... " << std::endl;
    gameObject->start();
    std::cout << "done calling start(). \n\n\n\n\n" << std::endl;
    gameObject->loopGame();
    std::cout << "done calling loopGame().  sleeping...\n\n\n\n\n" << std::endl;
    sleep( 1 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 1 );
    sleep( 1 );
    std::cout << "next player 1 score wins..." << std::endl;
    score( gameObject, gameState, 1 );
    std::cout << "player 1 won!" << std::endl;
    std::cout << "presumably done with test 1." << std::endl;
    sleep( 3 ); }

void test_02( GameObject* gameObject, GameState* gameState, int* loop_count ) {
    gameObject->getScoreBoard()->clearScreen();
    playerWin( gameObject, gameState, 1 );
    playerWin( gameObject, gameState, 2 );
    playerWin( gameObject, gameState, 1 );
    playerWin( gameObject, gameState, 2 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 1 );    
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 1 );
    playerWin( gameObject, gameState, 1 );
    score(     gameObject, gameState, 2 ); // player 2 needs to bump the serve 1st
    playerWin( gameObject, gameState, 2 );
    score(     gameObject, gameState, 2 );
    playerWin( gameObject, gameState, 2 );
    score(     gameObject, gameState, 2 );
    playerWin( gameObject, gameState, 2 );
    std::cout << " ready for player 1 set win..." << std::endl;
    playerWin( gameObject, gameState, 1 );
    std::cout << "player 1 won the set!" << std::endl;
    sleep( 2 ); }

void test_03( GameObject* gameObject, GameState* gameState, int* loop_count ) {
    gameObject->getScoreBoard()->clearScreen();
    Undo* undo = gameObject->createUndo(); // undo object
    undo->setScoreBoard( gameObject->getScoreBoard());
    sleep( 1 );
    undo->mode1Undo( gameObject->getHistory());
    sleep( 1 );
    playerWin( gameObject, gameState, 2 );
    playerWin( gameObject, gameState, 2 );
    playerWin( gameObject, gameState, 2 );
    playerWin( gameObject, gameState, 2 );
    sleep( 2 );
    std::cout << " ready for player 1 set win..." << std::endl;
    playerWin( gameObject, gameState, 1 );
    std::cout << "player 1 won the set!" << std::endl;
    sleep( 4 ); }

int main( int argc, char *argv[]) {
    int loop_count = 0;
    std::cout << "creating GameObject..." << std::endl;
    std::cout << "creating GameState..." << std::endl;
    GameState*  gameState  = new GameState();  // make this 1st!!! cost me 3 days of debugging
    std::cout << "creating GameObject..." << std::endl;
    GameObject* gameObject = new GameObject( gameState );
    std::cout << "done creating game object.  sleeping...\n\n\n\n\n" << std::endl;
    sleep( .5 );
    std::cout << "done sleeping.  calling gameObject->loopGame()..." << std::endl;
    gameObject->loopGame();
    std::cout << "done calling loopGame().  sleeping...\n\n\n\n\n" << std::endl;
    sleep( .5 );
    std::cout << "manual set to: " << manual << std::endl;
    if ( manual == 1 ) { run_manual_game( gameObject, gameState, 1 ); return 0; } 
    ///// run tests /////
    int test_count = 0;
    writeMessage( gameObject, "t " + std::to_string( ++test_count ));
    std::cout << "calling test_01()..." << std::endl;
    test_01( gameObject, gameState, &loop_count );

    writeMessage( gameObject, "t " + std::to_string( ++test_count ));
    std::cout << "calling test_02()..." << std::endl;
    test_02( gameObject, gameState, &loop_count );

    writeMessage( gameObject, "t " + std::to_string( ++test_count ));
    std::cout << "calling test_03()..." << std::endl;
    test_03( gameObject, gameState, &loop_count ); }
```
    -Create a unit test for test_03.  Remember to put the game into the correct state before running the test.
    - Use the following source code as a template for your unit test:
```cpp
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
        undoObj = new Undo( player1, player2, pinInterface, gameState );
        undoObj->setScoreBoard( new ScoreBoard( player1, player2, gameState )); }

    void TearDown() override {
        delete mode1Score;
        delete scoreBoard;
        delete player1;
        delete player2;
        delete gameState;
        delete history; 
        delete pinInterface;
        delete pinState; 
        std::cout << "\n\n" << std::endl; }};

TEST_F( Mode1ScoreTest, TestFirstScore ) {   
    std::cout << "make sure player scores are 0" << std::endl;
    ASSERT_EQ( 0, player1->getPoints());
    ASSERT_EQ( 0, player2->getPoints());
    std::cout << "increment player 1 score" << std::endl;
    player1->setPoints( 1 );
    mode1Score->updateScore( player1 );
    ASSERT_EQ( "PLAYER 1: ////// I 15 //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   00 //////", scoreBoard->drawPlayerScore( player2 )); }


TEST_F( Mode1ScoreTest, TestPlayerPointsEqualOpponentPoints) {
    std::cout << "TestPlayerPointsEqualOpponentPoints..." << std::endl;
    player1->setPoints( 3 );
    player2->setPoints( 3 );
    mode1Score->updateScore( player1 );                                          
    ASSERT_EQ( 3, player1->getPoints());
    ASSERT_EQ( 3, player2->getPoints());           
    std::cout << " finished TestPlayerPointsEqualOpponentPoints." << std::endl; }

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
    EXPECT_EQ( player2->getPoints(), 2 );            // Assert
    ASSERT_EQ( "PLAYER 1: ////// I 40 //////", scoreBoard->drawPlayerScore( player1 ));
    ASSERT_EQ( "PLAYER 2: //////   30 //////", scoreBoard->drawPlayerScore( player2 )); }
```
    - Do not abbreviate any code.
    - Write your output to a downloadable C++ file.
    - Remember to put the game into the correct state before running the test.
    - Please begin writing the unit test for test_03.

https://chat.openai.com/share/a10d749d-7b6b-41ea-aa3f-2c185f0d4ded