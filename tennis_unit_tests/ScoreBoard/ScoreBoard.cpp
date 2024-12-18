#include "ScoreBoard.h"

ScoreBoard::ScoreBoard( Player* player1, Player* player2, GameState* gameState ):
    _player1( player1 ), _player2( player2 ), _gameState( gameState ) { 
    if ( onRaspberryPi() == false ) {
        std::cout << "constructing scoreboard without matrix..." << std::endl;
    } else {
        printf( "setting up matrix...\n" );
        Color pipe_color( 255, 255, 0 ); // yellow
        Color background_color( 0, 0, 0 );
        Color player_one_score_color( 0, 255, 0 ); // green
        Color player_two_score_color( 255, 0, 0 ); // red
        Color outline_color( 0, 0, 0 );
        RGBMatrix::Options matrix_options; // seems like the only logical place to create the canvas
        matrix_options.hardware_mapping = "regular";  // or e.g. "adafruit-hat"
        matrix_options.pixel_mapper_config = "Rotate:180;264-Mapper"; // or e.g. "U-mapper"
        matrix_options.rows = 64;
        matrix_options.cols = 64;
        matrix_options.chain_length = 1;
        matrix_options.parallel = 2;
        matrix_options.show_refresh_rate = false;
        matrix_options.disable_hardware_pulsing = true; // --led-no-hardware-pulse
        matrix_options.brightness = 35; // 35 is best for demo videos in largo
        matrix_options.pwm_bits = 11;
        matrix_options.multiplexing = 1;
        rgb_matrix::RuntimeOptions runtime_opt;
        runtime_opt.drop_privileges = 0;
        runtime_opt.gpio_slowdown = 2;
        runtime_opt.daemon = 0;
        runtime_opt.do_gpio_init = 1;
        printf( "Matrix options:\n" );
        printf( "  rows: %d\n", matrix_options.rows );
        printf( "  chain_length: %d\n", matrix_options.chain_length );
        printf( "  parallel: %d\n", matrix_options.parallel );
        printf( "  pwm_bits: %d\n", matrix_options.pwm_bits );
        printf( "  pwm_lsb_nanoseconds: %d\n", matrix_options.pwm_lsb_nanoseconds );
        printf( "  Runtime options:\n" );
        printf( "  daemon: %d\n", runtime_opt.daemon );
        printf( "  do_gpio_init: %d\n", runtime_opt.do_gpio_init );
        printf( "  drop_privileges: %d\n", runtime_opt.drop_privileges );
        printf( "  gpio_slowdown: %d\n", runtime_opt.gpio_slowdown );
        CanvasCreator canvasCreator( matrix_options, runtime_opt );
        _canvas = std::unique_ptr<rgb_matrix::RGBMatrix>( canvasCreator.createCanvas());
        FontLoader fontLoader( "fonts/mspgothic_042623.bdf" ); // Load Fonts
        rgb_matrix::Font font;
        fontLoader.LoadFont( font );
        FontLoader bigNumberFontLoader( "fonts/fgm_27_ee.bdf" );
        rgb_matrix::Font bigNumberFont;
        bigNumberFontLoader.LoadFont( bigNumberFont );
        if (!_big_number_font.LoadFont( BIG_NUMBER_FONT )) {
            fprintf( stderr, "Couldn't load font '%s'\n", BIG_NUMBER_FONT ); exit( 1 );}

        Color color( 255, 255, 0 );
        Color bg_color( 0, 0, 0 );
        Color blue_color( 0, 0, 255 );

        _playerOneScoreDrawer   = std::make_unique<Drawer>(
            _canvas.get(), &_big_number_font, Drawer::BIG, player_one_score_color, bg_color );
        _playerTwoScoreDrawer   = std::make_unique<Drawer>(
            _canvas.get(), &_big_number_font, Drawer::BIG, player_two_score_color, bg_color );

        _drawer = std::make_unique<Drawer>( _canvas.get(), &_big_number_font, Drawer::SMALL, color, bg_color );
        _pipeDrawer        = std::make_unique<Drawer>( _canvas.get(), &_big_number_font, Drawer::BIG, color, bg_color   );
        _bluePipeDrawer   = std::make_unique<Drawer>( _canvas.get(), &_big_number_font, Drawer::BIG, blue_color, bg_color );
        _setDrawer         = std::make_unique<SetDrawer>(    _canvas.get(), _gameState                                              );
        } // fi
    update();
}

ScoreBoard::~ScoreBoard() {
    // std::cout << "destroying ScoreBoard..." << std::endl;
    if ( _canvas != NULL ) {
        std::cout << "NOT deleting _canvas..." << std::endl;
        // delete _canvas.get(); // this causes some error.  only one scoreBoard is created anyway.
    } else { /* std::cout << "*** WARNING: _canvas == NULL, not deleting. ***" << std::endl; */ }}

void ScoreBoard::drawText( std::string message, int color, int x, int y ) {
    if ( onRaspberryPi() == false ) { std::cout << "/// " << message << " ///" << std::endl; return; }
    FontLoader bigNumberFontLoader( LITTLE_NUMBER_FONT );
    rgb_matrix::Font big_number_font;
    bigNumberFontLoader.LoadFont( big_number_font );
    if (!big_number_font.LoadFont( LITTLE_NUMBER_FONT )) {
        fprintf( stderr, "Couldn't load font '%s'\n", LITTLE_NUMBER_FONT ); exit( 1 );}
    Color fg_color = _getColor(color);
    Color bg_color( 0, 0, 0 );
    Drawer drawer( _canvas.get(), &big_number_font, Drawer::SMALL, fg_color, bg_color );
    drawer.drawText( message, x, y );
}

Color ScoreBoard::_getColor( int color_constant ) {
    switch ( color_constant ) {
        case RED:    return Color( 255, 0, 0 );
        case GREEN:  return Color( 0, 255, 0 );
        case BLUE:   return Color( 0, 0, 255 );
        case YELLOW: return Color( 255, 255, 0 );
        case ORANGE: return Color( 255, 165, 0 );
        case PURPLE: return Color( 128, 0, 128 );
        case WHITE:  return Color( 255, 255, 255 );
        case BLACK:  return Color( 0, 0, 0 );
        default:       return Color( 0, 0, 0 ); }
}

void ScoreBoard::writeMessage( std::string message ) {
    std::cout << "inside ScoreBoard::_writeMessage()..." << std::endl;
    if ( hasCanvas() == false ) {
        std::cout << "/// " << message << " ///" << std::endl;
    } else {
        std::cout << "the matrix should be constructed at this point.  writing message..." << std::endl;
        Color color( 255, 255, 0 );
        Color bg_color( 0, 0, 0 );
        int baseline = _big_number_font.baseline();            // set the coordinates for the text
        int first_offset  = 2;
        _drawer->drawNumber( message, first_offset, baseline + _big_number_font.height());
        std::cout << "inside ScoreBoard::writeMessage(), sleeping for 3 seconds..." << std::endl;
        GameTimer::gameDelay( 3000 );
        std::cout << "done sleeping." << std::endl; }}

void ScoreBoard::drawGames() {  std::cout << "inside ScoreBoard::drawGames()" << std::endl; }

RGBMatrix* ScoreBoard::getCanvas() { return _canvas.get(); }

bool ScoreBoard::hasCanvas() {
    if ( _canvas != NULL ) { return true;
    } else { /* std::cout << "*** WARNING: canvas is NULL ***" << std::endl; */ return false; }}

void ScoreBoard::update() {
    // std::cout << "inside ScoreBoard::update() ... " << std::endl;
    // std::cout << "checking for _player1 or _player2 null values..." << std::endl;
    if ( _player1 == nullptr ) {
        std::cout << "*** ERROR: _player1 == NULL ***" << std::endl;
        exit( 1 ); }
    if ( _player2 == nullptr ) {
        std::cout << "*** ERROR: _player2 == NULL ***" << std::endl;
        exit( 1 ); }
    // std::cout << "gamestate current action: " << _gameState->getCurrentAction() << std::endl;
    clearScreen();
    std::cout << "inside ScoreBoard::update()  player1 points: " << _player1->getPoints() << std::endl;
    std::cout << "inside ScoreBoard::update()  player2 points: " << _player2->getPoints() << std::endl;
    drawPlayerScore( _player1 );
    drawPlayerScore( _player2 );
    // _setDrawer->drawSets();

    std::cout << "scoreboard has a canvas.  checking for blink in action..." << std::endl;
    bool blink = _gameState->getCurrentAction().find( "blink" ) != std::string::npos;
    if ( blink ) {
        std::cout << "blink is true, calling _setDrawer->drawBlinkSets()..." << std::endl;
        std::cout << "gamestate current action: " << _gameState->getCurrentAction() << std::endl;
        int playerToBlink = _gameState->getCurrentAction().find( "player1" ) != std::string::npos ?
            PLAYER_1_INITIALIZED : PLAYER_2_INITIALIZED;
        _setDrawer->drawBlinkSets( playerToBlink ); // checks current action ignoring playerToBlink
    } else { _setDrawer->drawSets(); }

    if ( _gameState->getTieBreak() == true ) {
        std::cout << "tie break is true, calling _drawTieBreakerBar()..." << std::endl;
        _drawTieBreakerBar();
    } else { std::cout << "tie break is false, not calling _drawTieBreakerBar()..." << std::endl; }
}

void ScoreBoard::_drawTieBreakerBar() {
    _bluePipeDrawer->drawNumber( "I", BLUE_BAR_HORIZONTAL_OFFSET, BLUE_BAR_VERTICAL_OFFSET ); // draw pipe
}

void ScoreBoard::clearScreen() {
    if ( hasCanvas() == false ) {
        std::cout << "clearScreen called, no matrix." << std::endl;
    } else {
        if ( !hasCanvas()) { std::cout << "*** ERROR: canvas == NULL.  exiting... ***" << std::endl; exit( 1 ); }
        std::cout << "clearScreen called, hasCanvas() is good.  clearing matrix...." << std::endl;
        Color flood_color( 0, 0, 0 ); _canvas->Fill( flood_color.r, flood_color.g, flood_color.b ); }}

std::string ScoreBoard::drawPlayerScore( Player* player ) {
    std::string serve_bar = _gameState->getServe() == player->number() ? "I" : " "; // or p1 serve and swap
    std::string score = _translate( player->getPoints());
    if( hasCanvas() == false ) {
        player->number() == PLAYER_1_INITIALIZED ?  // type player 1 score, else type player 2 score
        std::cout << "PLAYER 1: ////// " << serve_bar << " " << score << " ////// " << std::endl :
        std::cout << "PLAYER 2: ////// " << serve_bar << " " << score << " ////// " << std::endl;
    } else {
        int vertical_offset = player->number() == 0 ? 0 : _big_number_font.height();
        _pipeDrawer->drawNumber( serve_bar, 1, _big_number_font.baseline() + vertical_offset ); // draw pipe
        int baseline = _big_number_font.baseline();                  // set the coordinates for the text
        int first_offset  = _characterOffset( score.substr( 0, 1 ));
        int second_offset = ( score.length() > 1 ) ? _characterOffset( score.substr( 1, 1 )) : 0;
        if( player->number() == PLAYER_1_INITIALIZED ) { // then draw text depending on player
            _playerOneScoreDrawer->drawNumber( score.substr( 0, 1 ), first_offset  + 16, baseline + vertical_offset );
            if ( score.length() > 1 ) {
                _playerOneScoreDrawer->drawNumber( score.substr( 1, 1 ), second_offset + 38, baseline + vertical_offset ); }
        } else {
            _playerTwoScoreDrawer->drawNumber( score.substr( 0, 1 ), first_offset  + 16, baseline + vertical_offset );
            if ( score.length() > 1 ) {
                _playerTwoScoreDrawer->drawNumber( score.substr( 1, 1 ), second_offset + 38, baseline + vertical_offset ); }
        } // return player 1 score, else type player 2 score
    }
    // created a concatenated string with "PLAYER 1: ////// " + serve_bar
    std::string returnString = "*** WARNING: return string is not set. this is not normal ***";
    std::string player1ScoreString = "PLAYER 1: ////// " + serve_bar + " " + score + " //////";
    std::string player2ScoreString = "PLAYER 2: ////// " + serve_bar + " " + score + " //////";
    player->number() == PLAYER_1_INITIALIZED ?
    returnString = player1ScoreString : returnString = player2ScoreString;
    return returnString;
}

int ScoreBoard::_characterOffset( std::string character ) {
    int char_offset = 0;
    if ( character == "A" ) {
        return -4;
    } else if ( character == "d" ) {
        return 0;
    } else { char_offset = std::stoi( character ); }

    switch ( char_offset ) {
    case 3: return -1;
    case 4: return -4;
    case 5: return -1;
    default: return 0; }}

std::string ScoreBoard::_translate( int raw_score ) {
    if( _gameState->getTieBreak() == false ) {
        switch ( raw_score ) {
        case 0:               return "00";
        case 1:               return "15";
        case 2:               return "30";
        case 3:               return "40";

        case SCORE_CASE_4:
            if ( _gameState->getPointFlash()) {
                return "Ad";
            } else {
                return "40";
            }

        case SCORE_CASE_5:    return "Ad";
        case UNDEFINED_SCORE: return "99";
        default:              return "00"; }
    } else {
        switch ( raw_score ) {
            case 0:               return "0";
            case 1:               return "1";
            case 2:               return "2";
            case 3:               return "3";
            case 4:               return "4";
            case 5:               return "5";
            case 6:               return "6";
            case 7:               return "7";
            case 8:               return "8";
            case 9:               return "9";
            case 10:              return "10";
            case 11:              return "11";
            case 12:              return "12";
            case 13:              return "13";
            case 14:              return "14";
            case 15:              return "15";
        }
    }
    return "*** ERROR: can not translate. ***"; }

bool ScoreBoard::onRaspberryPi() {
    std::ifstream file("/proc/device-tree/model");
    std::string line;
    if (file.is_open()) {
        std::getline(file, line);
        file.close();
        if (line.find("Raspberry Pi") != std::string::npos) { return true; }
    }
    return false; }