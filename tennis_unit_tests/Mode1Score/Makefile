CXX := g++  # Compiler settings
CXXFLAGS := -std=c++14 -Wall -Wextra -g

SRC_DIR   := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score  # Directories
TEST_DIR  := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score
BUILD_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score

# Google Test and Google Mock directories
GTEST_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib
GMOCK_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib

# Object files and dependencies
TEST_OBJ := $(BUILD_DIR)/FontLoader.o $(BUILD_DIR)/SetDrawer.o $(BUILD_DIR)/ScoreBoard.o $(BUILD_DIR)/PointLeds.o $(BUILD_DIR)/GameState.o $(BUILD_DIR)/Mode1Score.o $(BUILD_DIR)/Mode1ScoreTest.o $(BUILD_DIR)/Mode1TieBreaker.o $(BUILD_DIR)/PinState.o $(BUILD_DIR)/Player.o $(BUILD_DIR)/TranslateConstant.o $(BUILD_DIR)/WinSequences.o
DEPS := $(GTEST_DIR)/libgtest.a $(GTEST_DIR)/libgtest_main.a $(GMOCK_DIR)/libgmock.a $(GMOCK_DIR)/libgmock_main.a

TARGET := $(BUILD_DIR)/Mode1ScoreTest  # Main target (unit tests)

.PHONY: all clean # Targets

all: $(TARGET)

$(TARGET): $(TEST_OBJ) $(DEPS)  # Build the unit test executable
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(TEST_OBJ) -o $@ -lgmock_main -lgmock -lgtest -lpthread

$(BUILD_DIR)/%.o: %.cpp # Compile the unit test source file
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/FontLoader.o: ../FontLoader/FontLoader.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/SetDrawer.o: ../SetDrawer/SetDrawer.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/ScoreBoard.o: ../ScoreBoard/ScoreBoard.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/WinSequences.o: ../WinSequences/WinSequences.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/ServeLeds.o: ../ServeLeds/ServeLeds.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/PointLeds.o: ../PointLeds/PointLeds.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/SetLeds.o: ../SetLeds/SetLeds.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/GameLeds.o: ../GameLeds/GameLeds.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/GameState.o: ../GameState/GameState.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/Player.o: ../Player/Player.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile the Mode1TieBreaker, Mode1Score, and TranslateConstant source files
$(BUILD_DIR)/Mode1TieBreaker.o: ../Mode1TieBreaker/Mode1TieBreaker.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/PinState.o: ../PinState/PinState.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/Mode1Score.o: Mode1Score.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/TranslateConstant.o: ../TranslateConstant/TranslateConstant.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(GTEST_DIR)/libgtest_main.a:  # Google Test and Google Mock dependencies
$(GMOCK_DIR)/libgmock_main.a:

clean:                          # Clean build artifacts
	find $(BUILD_DIR) -type f -name '*.o' -delete
	rm -f $(TARGET)
