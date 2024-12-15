# Your role
- Expert C++ Developer
- World-class Developer of tennis scoring systems

# Your task
- Use the Player::getOpponent() method to combine the playerOneMatchWin() and playerTwoMatchWin() methods into one method called matchWin( *Player player ).

## Player 1 Match win C++ source code
```cpp
void Mode1WinSequences::p1MatchWinSequence() {
    std::cout << "//////////////////////// p1MatchWinSequence() ////////////////////////" << std::endl;
    if ( _scoreBoard->hasCanvas()) {
        std::cout << "scoreboard has canvas.  updating..." << std::endl;
    } else {
        _undo.memory();
        _pointLeds.updateTBPoints();
        MatchWinSequence matchWinSequence;
        matchWinSequence.run( _player1, _gameState, &_gameLeds, &_setLeds );
        _reset.resetScoreboard(); }}
```

## Player 2 Match win C++ source code
```cpp
void Mode1WinSequences::p2MatchWinSequence() {
    std::cout << "//////////////////////// p2MatchWinSequence() ////////////////////////" << std::endl;
    _undo.memory();               
    _pointLeds.updateTBPoints();
    _player1->setGames( 5 );
    _gameLeds.updateGames();      
    MatchWinSequence matchWinSequence; matchWinSequence.run( _player2, _gameState, &_gameLeds, &_setLeds );
    _reset.resetScoreboard();}
```

## Player Object C++ source code
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