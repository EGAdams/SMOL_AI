#include "../googletest/googlemock/include/gmock/gmock.h"
#include "IGameState.h"
#include "../Player/IPlayerMock.h"

class IGameStateMock : public IGameState {
public:
    // game flash delay
    MOCK_METHOD( void, setGameFlashDelay, (( int ) gameFlashDelay), (override) );
    MOCK_METHOD(( int ), getGameFlashDelay, (), (override));
    MOCK_METHOD( int, getUpdateDisplayDelay, (), (override) );
    MOCK_METHOD( void, stopGameRunning, (), (override) );
    MOCK_METHOD( int, gameRunning, (), (override) );
    MOCK_METHOD( void, setGameHistory, (( std::map<int, int>) game_history), (override) );
    MOCK_METHOD(( std::map< int, int >), getGameHistory, (), (override));
    MOCK_METHOD( void, setCurrentAction, (( std::string) currentAction), (override) );
    MOCK_METHOD(( std::string ), getCurrentAction, (), (override));
    MOCK_METHOD( void, setCurrentSet, (( int) current_set), (override) );
    MOCK_METHOD(( int ), getCurrentSet, (), (override));
    MOCK_METHOD( void, setWinDelay, (( int) winDelay), (override) );
    MOCK_METHOD(( int ), getWinDelay, (), (override));
    MOCK_METHOD( void, setPointFlash, (( int) pointFlash), (override) );
    MOCK_METHOD(( int ), getPointFlash, (), (override));
    MOCK_METHOD( void, setServe, (( int) serve), (override) );
    MOCK_METHOD(( int ), getServe, (), (override));
    MOCK_METHOD( void, setTieBreak, (( int) tieBreak), (override) );
    MOCK_METHOD(( int ), getTieBreak, (), (override));
    MOCK_METHOD( void, setTieLEDsOn, (( int) tieLEDsOn), (override) );
    MOCK_METHOD(( int ), getTieLEDsOn, (), (override));
    MOCK_METHOD( void, setServeSwitch, (( int) serveSwitch), (override) );
    MOCK_METHOD(( int ), getServeSwitch, (), (override));
    MOCK_METHOD( void, setPlayerButton, (( int) playerButton), (override) );
    MOCK_METHOD(( int ), getPlayerButton, (), (override));
    MOCK_METHOD( void, setUndo, (( int) undo), (override) );
    MOCK_METHOD(( int ), getUndo, (), (override));
    MOCK_METHOD( void, setStarted, (( int) started), (override) );
    MOCK_METHOD(( int ), getStarted, (), (override));
    MOCK_METHOD( void, setSetTieBreak, (( int) setTieBreak), (override) );
    MOCK_METHOD(( int ), getSetTieBreak, (), (override));
    MOCK_METHOD( void, setRotaryChange, (( int) rotaryChange), (override) );
    MOCK_METHOD(( int ), getRotaryChange, (), (override));
    MOCK_METHOD( void, setPreviousTime, (( unsigned long) previousTime), (override) );
    MOCK_METHOD(( unsigned long ), getPreviousTime, (), (override));
    MOCK_METHOD( void, setRotaryPosition, (( int) rotaryPosition), (override) );
    MOCK_METHOD(( int ), getRotaryPosition, (), (override));
    MOCK_METHOD( void, setPrevRotaryPosition, (( int) prevRotaryPosition), (override) );
    MOCK_METHOD(( int ), getPrevRotaryPosition, (), (override));
    MOCK_METHOD( void, setFreezePlayerButton, (( int) freezePlayerButton), (override) );
    MOCK_METHOD(( int ), getFreezePlayerButton, (), (override));
    MOCK_METHOD( void, setP1PointsMem, (( int) p1PointsMem), (override) );
    MOCK_METHOD(( int ), getP1PointsMem, (), (override));
    MOCK_METHOD( void, setP2PointsMem, (( int) p2PointsMem), (override) );
    MOCK_METHOD(( int ), getP2PointsMem, (), (override));
    MOCK_METHOD( void, setP1GamesMem, (( int) p1GamesMem), (override) );
    MOCK_METHOD(( int ), getP1GamesMem, (), (override));
    MOCK_METHOD( void, setP2GamesMem, (( int) p2GamesMem), (override) );
    MOCK_METHOD(( int ), getP2GamesMem, (), (override));
    MOCK_METHOD( void, setP1SetsMem, (( int) p1SetsMem), (override) );
    MOCK_METHOD(( int ), getP1SetsMem, (), (override));
    MOCK_METHOD( void, setP2SetsMem, (( int) p2SetsMem), (override) );
    MOCK_METHOD(( int ), getP2SetsMem, (), (override));
    
    // get rotary position
    MOCK_METHOD( void, setRotaryPosition, (( int) rotaryPosition), (override) );
    MOCK_METHOD(( int ), getRotaryPosition, (), (override));

    // current set
    MOCK_METHOD( void, setCurrentSet, (( int) current_set), (override) );
    MOCK_METHOD(( int ), getCurrentSet, (), (override));
    // win delay
    MOCK_METHOD( void, setWinDelay, (( int) winDelay), (override) );
    MOCK_METHOD(( int ), getWinDelay, (), (override));
    // serve
    MOCK_METHOD( void, setServe, (( int) serve), (override) );
    MOCK_METHOD(( int ), getServe, (), (override));
    // tie break
    MOCK_METHOD( void, setTieBreak, (( int) tieBreak), (override) );
    MOCK_METHOD(( int ), getTieBreak, (), (override));
    // tie LEDs on
    MOCK_METHOD( void, setTieLEDsOn, (( int) tieLEDsOn), (override) );
    MOCK_METHOD(( int ), getTieLEDsOn, (), (override));
    // serve switch
    MOCK_METHOD( void, setServeSwitch, (( int) serveSwitch), (override) );
    MOCK_METHOD(( int ), getServeSwitch, (), (override));
    // player button
    MOCK_METHOD( void, setPlayerButton, (( int) playerButton), (override) );
    MOCK_METHOD(( int ), getPlayerButton, (), (override));
    // undo
    MOCK_METHOD( void, setUndo, (( int) undo), (override) );
    MOCK_METHOD(( int ), getUndo, (), (override));
    // previous time
    MOCK_METHOD( void, setPreviousTime, (( unsigned long) previousTime), (override) );
    MOCK_METHOD(( unsigned long ), getPreviousTime, (), (override));
    // rotary position
    MOCK_METHOD( void, setRotaryPosition, (( int) rotaryPosition), (override) );
    MOCK_METHOD(( int ), getRotaryPosition, (), (override));
 
    // p1 points mem
    MOCK_METHOD( void, setP1PointsMem, (( int) p1PointsMem), (override) );
    MOCK_METHOD(( int ), getP1PointsMem, (), (override));

    // p2 sets mem
    MOCK_METHOD( void, setP2SetsMem, (( int) p2SetsMem), (override) );
    MOCK_METHOD(( int ), getP2SetsMem, (), (override));
    // now
    MOCK_METHOD( void, setNow, (( unsigned long) now), (override) );
    MOCK_METHOD(( unsigned long ), getNow, (), (override));

    // toggle
    MOCK_METHOD( void, setToggle, (( int) toggle), (override) );
    MOCK_METHOD(( int ), getToggle, (), (override));
    // tieBreakOnly
    MOCK_METHOD( void, setTieBreakOnly, (( int) tieBreakOnly), (override) );
    MOCK_METHOD(( int ), getTieBreakOnly, (), (override));
    // delays

    MOCK_METHOD( void, setWinDelay, (( int) winDelay), (override) );
    MOCK_METHOD(( int ), getWinDelay, (), (override));
    // button delay
    MOCK_METHOD( void, setButtonDelay, (( int) buttonDelay), (override) );
    MOCK_METHOD(( int ), getButtonDelay, (), (override));
    // flash delay
    MOCK_METHOD( void, setFlashDelay, (( unsigned long ) flashDelay), (override) );
    MOCK_METHOD(( unsigned long ), getFlashDelay, (), (override));
    // set tie break mem
    MOCK_METHOD( void, setTieBreakMem, (( int) setTieBreakMem), (override) );
    MOCK_METHOD(( int ), getTieBreakMem, (), (override));    

    MOCK_METHOD( void, setSetTieBreakMem, (( int ) setTieBreakMem ), ( override ));
    MOCK_METHOD(( int ), getSetTieBreakMem, (), ( override ));
    // player 1 points
    MOCK_METHOD( void, setPlayer1Points, (( int ) player1Points ), ( override ));
    MOCK_METHOD(( int ), getPlayer1Points, (), ( override ));
    // player 2 points
    MOCK_METHOD( void, setPlayer2Points, (( int ) player2Points ), ( override ));
    MOCK_METHOD(( int ), getPlayer2Points, (), ( override ));
    // player 1 games
    MOCK_METHOD( void, setPlayer1Games, (( int ) player1Games ), ( override ));
    MOCK_METHOD(( int ), getPlayer1Games, (), ( override ));
    // player 2 games
    MOCK_METHOD( void, setPlayer2Games, (( int ) player2Games ), ( override ));
    MOCK_METHOD(( int ), getPlayer2Games, (), ( override ));
    // player 1 sets
    MOCK_METHOD( void, setPlayer1Sets, (( int ) player1Sets ), ( override ));
    MOCK_METHOD(( int ), getPlayer1Sets, (), ( override ));
    // player 2 sets
    MOCK_METHOD( void, setPlayer2Sets, (( int ) player2Sets ), ( override ));
    MOCK_METHOD(( int ), getPlayer2Sets, (), ( override ));
    // player 1 matches
    MOCK_METHOD( void, setPlayer1Matches, (( int ) player1Matches ), ( override ));
    MOCK_METHOD(( int ), getPlayer1Matches, (), ( override ));
    // player 2 matches
    MOCK_METHOD( void, setPlayer2Matches, (( int ) player2Matches ), ( override ));
    MOCK_METHOD(( int ), getPlayer2Matches, (), ( override ));
    // pulse count
    MOCK_METHOD( void, setGameWinPulseCount, (( int ) gameWinPulseCount ), ( override ));
    MOCK_METHOD(( int ), getGameWinPulseCount, (), ( override ));
    // player 1 set history
    MOCK_METHOD( void, setPlayer1SetHistory, (( std::map<int, int> ) player1_set_history ), ( override ));
    MOCK_METHOD(( std::map<int, int> ), getPlayer1SetHistory, (), ( override ));
    // player 2 set history
    MOCK_METHOD( void, setPlayer2SetHistory, (( std::map<int, int> ) player2_set_history ), ( override ));
    MOCK_METHOD(( std::map<int, int> ), getPlayer2SetHistory, (), ( override ));


};