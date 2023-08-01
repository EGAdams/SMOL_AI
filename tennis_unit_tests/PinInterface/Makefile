CXX := g++  # Compiler settings
CXXFLAGS := -std=c++14 -Wall -Wextra -g

SRC_DIR   := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface  # Directories
TEST_DIR  := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface
BUILD_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface

# Google Test and Google Mock directories
GTEST_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib
GMOCK_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib

# Object files and dependencies
TEST_OBJ := $(BUILD_DIR)/PinInterfaceTest.o $(BUILD_DIR)/PinState.o $(BUILD_DIR)/PinInterface.o $(BUILD_DIR)/TranslateConstant.o
DEPS := $(GTEST_DIR)/libgtest.a $(GTEST_DIR)/libgtest_main.a $(GMOCK_DIR)/libgmock.a $(GMOCK_DIR)/libgmock_main.a

TARGET := $(BUILD_DIR)/PinInterfaceTest  # Main target (unit tests)

.PHONY: all clean # Targets

all: $(TARGET)

$(TARGET): $(TEST_OBJ) $(DEPS)  # Build the unit test executable
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lgtest -lgtest_main -lpthread

$(BUILD_DIR)/%.o: %.cpp # Compile the unit test source file
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile the PinState, PinInterface, and TranslateConstant source files
$(BUILD_DIR)/PinState.o: ../PinState/PinState.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/PinInterface.o: PinInterface.cpp
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