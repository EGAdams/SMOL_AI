# Compiler settings
CXX := g++
CXXFLAGS := -std=c++14 -Wall -Wextra

# Directories
SRC_DIR   := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface
TEST_DIR  := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface
BUILD_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface

# Google Test and Google Mock directories
GTEST_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib
GMOCK_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib

# Object files and dependencies
TEST_OBJ := $(BUILD_DIR)/MockPinInterface.o $(BUILD_DIR)/PinState.o $(BUILD_DIR)/PinInterface.o $(BUILD_DIR)/TranslateConstant.o
DEPS := $(GTEST_DIR)/libgtest.a $(GTEST_DIR)/libgtest_main.a $(GMOCK_DIR)/libgmock.a $(GMOCK_DIR)/libgmock_main.a

# Main target (unit tests)
TARGET := $(BUILD_DIR)/MockPinInterfaceTest

# Targets
.PHONY: all clean

all: $(TARGET)

# Build the unit test executable
$(TARGET): $(TEST_OBJ) $(DEPS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lgtest -lgtest_main -lpthread

# Compile the unit test source file
$(BUILD_DIR)/%.o: %.cpp
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

# Google Test and Google Mock dependencies
$(GTEST_DIR)/libgtest_main.a:
        # Build Google Test if needed

$(GMOCK_DIR)/libgmock_main.a:
        # Build Google Mock if needed

# Clean build artifacts
clean:
	find $(BUILD_DIR) -type f -name '*.o' -delete
	rm -f $(TARGET)
