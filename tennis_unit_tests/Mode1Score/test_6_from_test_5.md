# Your roles
- World-class C++ developer
- Expert in writing Google unit tests for Tennis scoring systems
- Expert in writing Full Systems Tests for Tennis scoring systems
- My helpful assistant

# The information that we have
## Working Unit test that needs to be converted to a more full System test
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
        mode1Score->setScoreBoard( scoreBoard ); }

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

```

## Working Systems Test #5 source code
```cpp
void score( GameObject* gameObject, GameState* gameState, int player ) {
    gameObject->playerScore( player );  // flip the player score flag
    gameObject->loopGame();             // handle the player score flag
    std::map<int, int> _player1_set_history = gameState->getPlayer1SetHistory();
    std::map<int, int> _player2_set_history = gameState->getPlayer2SetHistory(); }

void playerWin( GameObject* gameObject, GameState* gameState, int player ) {
    score( gameObject, gameState, player );
    score( gameObject, gameState, player );
    score( gameObject, gameState, player );
    score( gameObject, gameState, player ); }

void test_05( GameObject* gameObject, GameState* gameState, int* loop_count ) {
    gameObject->getScoreBoard()->clearScreen();
    gameObject->getPlayer1()->setPoints( 0 );
    gameState->setPlayer1Points(         0 );
    gameObject->getPlayer2()->setPoints( 2 );
    gameState->setPlayer2Points(         2 );
    gameObject->getPlayer1()->setGames(  6 );
    gameObject->getPlayer2()->setGames(  5 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 2 );    // now to trigger the tie break...
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 2 );
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
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 1 );
    score( gameObject, gameState, 2 );
    score( gameObject, gameState, 2 );
    sleep( 6 ); }

int main( int argc, char *argv[]) {
    int loop_count = 0;
    test_05( gameObject, gameState, &loop_count ); }
```


# Your task
- Analyze the C++ Google Unit Test method `TEST_F( Mode1ScoreTest, Test_Two_Set_Win_Scenario )` and think about how we are going to convert this to a more full system test using the `Working Sysems Test #5 source code` only as a guide.
  
- Write a new Systems Test #6 that will run the following:
    - Set the correct state of the game object
    - Run the score method until player 1 wins the set
    - Run the score method until player 1 wins the set again
    - Since the match is won, std::cout <<  "match win" and end the game

 

 [ g4 answer](https://chat.openai.com/share/3cf6942b-79bc-458a-8a7a-8e74f10eb46f)