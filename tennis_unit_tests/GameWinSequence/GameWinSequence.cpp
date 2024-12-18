#include "GameWinSequence.h"

GameWinSequence::GameWinSequence()  {}
GameWinSequence::~GameWinSequence() {}

void GameWinSequence::run( Player* player, GameState* gameState, 
                           GameLeds* gameLeds, ScoreBoard* scoreBoard, int games_in_memory ) {
    
    if ( MATRIX_DISABLED == 1 ) { 
        std::cout << "GameWinSequence::run() MATRIX_DISABLED == 1, returning... " << std::endl; return; }
    if ( scoreBoard->hasCanvas()) {
        std::cout << "GameWinSequence::run() hasCanvas() == true" << std::endl;
        for ( int blink_sequence_count = 0; blink_sequence_count < LOOP_GAME_LAMP_WIN; blink_sequence_count++ ) {
            std::cout << "cloaking ... " << std::endl;
            std::cout << "setting blink for player number: " << player->number() << std::endl;
            player->number() == PLAYER_1_INITIALIZED ? gameState->setCurrentAction( "player1 blink" ) 
                                : gameState->setCurrentAction( "player2 blink" );
            std::cout << "gamestate current action: " << gameState->getCurrentAction() << std::endl;
            scoreBoard->update();
            std::cout << "uncloaking ... " << std::endl;
            GameTimer::gameDelay( GAME_FLASH_DELAY );  /*** wait ***/
            gameState->setCurrentAction( NORMAL_GAME_STATE );
            scoreBoard->update(); 
            GameTimer::gameDelay( GAME_FLASH_DELAY );  /*** wait ***/ }
    } else {
        std::cout << "GameWinSequence::run() hasCanvas() == false" << std::endl;
        for ( int blink_sequence_count = 0; blink_sequence_count < LOOP_GAME_LAMP_WIN; blink_sequence_count++ ) {  
            player->setGames( 5 );                    // set game count so game LEDs will turn off
            gameLeds->updateGames();                                // actually turn game LEDs off
            GameTimer::gameDelay( GAME_FLASH_DELAY );  /*** wait ***/
            player->setGames( games_in_memory );                    // restore game count in player object  
            gameLeds->updateGames();                                // turn players game point on
            GameTimer::gameDelay( GAME_FLASH_DELAY );  /*** wait ****/ }}}