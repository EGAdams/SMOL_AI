# Your Roles
	- Expert C++ Developer
	- My excellent teacher
	- My helpful assistant

# Your Task
	- Create a Makefile that will include the following unit test as a separate execution unit.  I am going to show you the unit test first, and then I will show you the Makefile that you will need to modify to include the unit test as a separate execution unit.

```cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Undo.h"
#include "../History/History.h"
#include "../Player/Player.h"

class UndoTest : public ::testing::Test {
protected:
    History* history;
    Undo* undoObj;
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
        player1->setOpponent( player2 ); 
        player2->setOpponent( player1 );
        history = new History();
        pin_map = {{ "pin", 0 }};
        pinState = new PinState( pin_map );
        pinInterface = new PinInterface( pinState );
        undoObj = new Undo( player1, player2, pinInterface, gameState );
    }

    void TearDown() override {
        delete undoObj;
        delete player1;
        delete player2;
        delete gameState;
        delete history; 
        delete pinInterface;
        delete pinState; 
        std::cout << "\n\n" << std::endl;
    }
};

TEST_F( UndoTest, TestSetMode1Undo ) {
    // Setup initial game state
    player1->setPoints( 3 );
    player2->setPoints( 2 );
    
    // Save the game state to history
    undoObj->snapshot( history );

    // Change the game state
    player1->setPoints( 5 );
    player2->setPoints( 4 );

    // Verify the changed game state
    ASSERT_EQ( 5, player1->getPoints());
    ASSERT_EQ( 4, player2->getPoints());

    // Restore game state from history
    undoObj->mode1Undo( history );

    // Verify restored game state
    ASSERT_EQ( 3, player1->getPoints());
    ASSERT_EQ( 2, player2->getPoints());
}
```
    - Please modify the following makefile to include the above unit test as a separate execution unit:

```makefile
# Variable definitions
GTEST_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib
GMOCK_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib


CXX = g++
CXXFLAGS = -Wall -Wextra -g -I$(GTEST_DIR)/include -I../../include
LDFLAGS = -L$(GTEST_DIR)/lib -L../../lib -lgtest -lgtest_main -lgmock -lgmock_main -lrgbmatrix -pthread
TARGET = run_tests

# Define our source and object files
SOURCES = Mode1Score.cpp Mode1ScoreTest.cpp          \
		  ../TieBreaker/TieBreaker.cpp     \
		  ../GameLeds/GameLeds.cpp			         \
		  ../GameTimer/GameTimer.cpp		 	     \
		  ../GameState/GameState.cpp			     \
		  ../GameWinSequence/GameWinSequence.cpp     \
		  ../GameLedTranslator/GameLedTranslator.cpp \
		  ../MatchWinSequence/MatchWinSequence.cpp 	 \
		  ../Inputs/Inputs.cpp					     \
		  ../Logger/Logger.cpp	   				     \
		  ../PointLeds/PointLeds.cpp			     \
		  ../PinState/PinState.cpp				     \
		  ../PinInterface/PinInterface.cpp		     \
		  ../Player/Player.cpp					     \
		  ../Reset/Reset.cpp					     \
		  ../ScoreBoard/ScoreBoard.cpp			     \
		  ../SetHistoryText/SetHistoryText.cpp	     \
		  ../SetLeds/SetLeds.cpp				     \
		  ../ServeLeds/ServeLeds.cpp			     \
		  ../SetWin/SetWin.cpp					     \
		  ../SetDrawer/SetDrawer.cpp			     \
		  ../Undo/Undo.cpp						     \
		  ../TennisConstants/TennisConstants.cpp     \
		  ../TieLeds/TieLeds.cpp				     \
		  ../History/History.cpp				     \
		  ../WatchTimer/WatchTimer.cpp			     \
		  ../FontLoader/FontLoader.cpp			     \
		  ../WinSequences/WinSequences.cpp		     \
		  ../TranslateConstant/TranslateConstant.cpp \

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

test: $(TARGET)
	./$(TARGET)
```
    - Do not abbreviate anything.
    - Write your output to a downloadable Makefile.