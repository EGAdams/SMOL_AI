# Variable definitions
GTEST_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib
GMOCK_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib


CXX = g++
CXXFLAGS = -Wall -Wextra -g -I$(GTEST_DIR)/include
LDFLAGS = -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread
TARGET = run_tests

# Define our source and object files
SOURCES = Mode1Score.cpp 					\
		  ../Mode1ScoreTest.cpp 			\
		  ../PointLeds/PointLeds.cpp		\
		  ../PinState/PinState.cpp			\
		  ../SetLeds/SetLeds.cpp			\
		  ../GameLeds/GameLeds.cpp			\
		  ../ServeLeds/ServeLeds.cpp		\
		  ../FontLoader/FontLoader.cpp		\
		  ../SetDrawer/SetDrawer.cpp		\
		  ../ScoreBoard/ScoreBoard.cpp		\
		  ../WinSequences/WinSequences.cpp	\
		  ../GameState/GameState.cpp		\
		  ../Mode1TieBreaker/Mode1TieBreaker.cpp	\
		  ../Player/Player.cpp				\
		  ../TranslateConstant/TranslateConstant.cpp \
		  ../Undo/Undo.cpp					\
		  ../GameTimer/GameTimer.cpp		\
		  ../GameLedTranslator/GameLedTranslator.cpp \
		  ../MatchWinSequence/MatchWinSequence.cpp \
		  ../Reset/Reset.cpp				\
		  ../WatchTimer/WatchTimer.cpp		\

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
