# Variable definitions
GTEST_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib
GMOCK_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib


CXX = g++
CXXFLAGS = -Wall -Wextra -g -I$(GTEST_DIR)/include
LDFLAGS = -L$(GTEST_DIR)/lib -lgtest -lgtest_main -lgmock -lgmock_main -pthread
TARGET = run_tests

# Define our source and object files
SOURCES = Mode1Score.cpp Mode1ScoreTest.cpp        \
		  ../Mode1TieBreaker/Mode1TieBreaker.cpp   \
		  ../GameLeds/GameLeds.cpp			       \
		  ../GameTimer/GameTimer.cpp		 	   \
		  ../GameState/GameState.cpp			   \
		  ../GameWinSequence/GameWinSequence.cpp   \
		  ../MatchWinSequence/MatchWinSequence.cpp \
		  ../Inputs/Inputs.cpp					   \
		  ../WinSequences/WinSequences.cpp	       \
		  ../PointLeds/PointLeds.cpp			   \
		  ../PinInterface/PinInterface.cpp		   \
		  ../Player/Player.cpp					   \
		  ../SetLeds/SetLeds.cpp				   \
		  ../ServeLeds/ServeLeds.cpp			   \
		  ../Undo/Undo.cpp						   \
		  ../TennisConstants/TennisConstants.cpp   \
		  ../History/History.cpp				   \
		  ../WatchTimer/WatchTimer.cpp			   \
		  ../WinSequences/WinSequences.cpp		   \

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