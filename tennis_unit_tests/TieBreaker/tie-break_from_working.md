# Your roles
- World class C++ developer
- Expert in writing Google unit tests for Tennis scoring systems

# Your task
- Use the working test #5 source code below as a working example.
- Create a comprehensive set of unit tests for the TieBreaker class run() method.
- Use the same coding convention as the working test #5 source code below preserving the same indentation and spacing around parenthesis, brackets, and braces.

## Working test #5 source code
```cpp
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

## TieBreaker source relevant to the test
```cpp
void TieBreaker::run( Player* currentPlayer ) { 
    _undo.memory(); 
    _gameState->setServe( _getServe()); // set the serve bar depending tie-break iteration
    _scoreBoard->update();
    Player* opponent = currentPlayer->getOpponent();

    if ( currentPlayer->getPoints() == TIE_BREAK_MAX_POINTS ) {
        _undo.snapshot( _history );                                   
        currentPlayer->setGames( currentPlayer->getGames() + 1 );     // increment games
        incrementSet();
        _scoreBoard->update();
        celebrate( currentPlayer );    // this is a win no matter what.
        GameTimer::gameDelay( 3000 );
        endTieBreak(); 
    } else if ( currentPlayer->getPoints() >= TIE_BREAK_WIN_BY_TWO  && 
        ( currentPlayer->getPoints() - opponent->getPoints() >= 2)) {
        _undo.snapshot( _history );                                   
        currentPlayer->setGames( currentPlayer->getGames() + 1 );     // increment games
        incrementSet();
        _scoreBoard->update();
        celebrate( currentPlayer );
        GameTimer::gameDelay( 3000 );
        endTieBreak(); 
    } else {
                               // needed to put this here otherwise tie break would
                               // be incremented even after a win.
        incrementIteration();  // need this to determine serve bar location
    }
}

void TieBreaker::endTieBreak() {
    tieLEDsOff();
    _iteration = 0;
    _player1->setPoints( 0 );
    _player2->setPoints( 0 );
    _player1->setGames(  0 );
    _player2->setGames(  0 );
    std::cout << "*** calling _pointLeds.updatePoints() from inside endTieBreak()... ***" << std::endl;
    _pointLeds.updatePoints();
    _gameLeds.updateGames();
    _gameState->setTieBreak(    0 );
    _gameState->setSetTieBreak( 0 );
    _gameState->setServeSwitch( 1 );
    _gameState->setServe( 0 );
    _scoreBoard->update(); }

void TieBreaker::setIteration( int iteration ) { _iteration = iteration; }
int  TieBreaker::getIteration() { return _iteration; }
void TieBreaker::incrementIteration() { 
    // std::cout << "Incrementing iteration in TieBreaker::incrementIteration()... " << std::endl;
    _iteration++; }

int TieBreaker::_getServe() {
    switch ( _iteration ) {
    case 1:
        return PLAYER_2_SERVE; // doesn't matter who scores here.  doesn't concern me.
        break;
    
    case 2:
        return PLAYER_2_SERVE;
        break;

    case 3:
        return PLAYER_1_SERVE;
        break;

    case 4:
        return PLAYER_1_SERVE;
        break;
    
    case 5:
        return PLAYER_2_SERVE;
        break;
    
    case 6:
        return PLAYER_2_SERVE;
        break;
    
    case 7:
        return PLAYER_1_SERVE;
        break;

    case 8:
        return PLAYER_1_SERVE;
        break;

    case 9:
        return PLAYER_2_SERVE;
        break;

    case 10:
        return PLAYER_2_SERVE;
        break;
    
    case 11:
        return PLAYER_1_SERVE;
        break;

    case 12:
        return PLAYER_1_SERVE;
        break;
    
    case 13:
        return PLAYER_2_SERVE;
        break;

    case 14:
        return PLAYER_2_SERVE;
        break;

    case 15:
        return PLAYER_1_SERVE;
        break;
    
    case 16:
        return PLAYER_1_SERVE;
        break;

    case 17:
        return PLAYER_2_SERVE;
        break;

    case 18:
        return PLAYER_2_SERVE;
        break;

    case 19:
        return PLAYER_1_SERVE;
        break;

    case 20:
        return PLAYER_1_SERVE;
        break;

    case 21:
        return PLAYER_2_SERVE;
        break;

    case 22:
        return PLAYER_2_SERVE;
        break;

    case 23:
        return PLAYER_1_SERVE;
        break;

    case 24:
        return PLAYER_1_SERVE;
        break;

    case 25:
        return PLAYER_2_SERVE;
        break;
    
    default:
        std::cout << "*** WARNING: _getServe() in TieBreaker.cpp is returning default value. ***"
                  << std::endl;
        std::cout << "The iteration is: " << _iteration << std::endl;
        return PLAYER_1_SERVE;
        break;
    }
}
```

## Player object source
```cpp
Player::Player( GameState* gamestate, int playerNumber ) : _gameState( gamestate ), _playerNumber( playerNumber ) {
        _points = 0; _games = 0; _sets = 0; _matches = 0; _mode = 0; _setting = 0; 
        _game_history[ 1 ] = 0; _game_history[ 2 ] = 0; _game_history[ 3 ] = 0;     // initialize game history
        _set_history[  1 ] = 0;  _set_history[ 2 ] = 0; _set_history[  3 ] = 0; }   // initialize set history
Player::~Player() {}

void Player::setServeSwitch( int serve_switch ) { _serve_switch = serve_switch; } 
int Player::getServeSwitch() { return _serve_switch; }
void Player::setOpponent( Player* opponent ) { _opponent = opponent; }                                  
Player* Player::getOpponent() { return _opponent; }
void Player::setSets( GameState* gameState, int sets ) {                         // sets this player's sets
    this->setSetHistory(      gameState->getCurrentSet(), _games               ); // and set history for both
    _opponent->setSetHistory( gameState->getCurrentSet(), _opponent->getGames()); // players
    if( _playerNumber == PLAYER_1_INITIALIZED ) { 
        gameState->setPlayer1SetHistory( this->getSetHistory());
        gameState->setPlayer2SetHistory( _opponent->getSetHistory()); }
    else {
        gameState->setPlayer1SetHistory( _opponent->getSetHistory());
        gameState->setPlayer2SetHistory( this->getSetHistory()); }
    _sets = sets; }                                          
int Player::getSets() { return _sets; }

void Player::setPoints(int points) { _points = points; } 
int Player::getPoints() {  return _points;  }

void Player::setGames( int games ) { 
    _set_history[ _gameState->getCurrentSet()] = games;
    number() == PLAYER_1_INITIALIZED ? 
        _gameState->setPlayer1Games( games ) : _gameState->setPlayer2Games( games );
    _games = games; }         

int Player::getGames() { return _games; }

void Player::setMatches(int matches) { _matches = matches; } int Player::getMatches() { return _matches; }
void Player::setMode(int mode) { _mode = mode; }             int Player::getMode() {    return _mode;    }
void Player::setSetting(int setting) { _setting = setting; } int Player::getSetting() { return _setting; }
int Player::incrementSetting() { return ++_setting; }
int Player::number() { 
    // std::cout << "Player::number() returning " << _playerNumber << std::endl;
    return _playerNumber; }

void Player::setSetHistory( int set, int games ) {
    std::cout << "setting set history for player " << number() << " set " << set << " to " << games << std::endl;
    _set_history[  set ] = games; 
    number() == PLAYER_1_INITIALIZED ? 
        _gameState->setPlayer1SetHistory( _set_history ) : _gameState->setPlayer2SetHistory( _set_history ); } 
std::map< int, int> Player::getSetHistory() { 
    return _set_history; }

void Player::setGameHistory( int game, int score ) { _game_history[ game ] = score; } 
std::map< int, int> Player::getGameHistory() { return _game_history;}
```