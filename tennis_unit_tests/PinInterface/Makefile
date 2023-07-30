# Compiler settings
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra

# Directories
SRC_DIR := /home/adamsl/SMOL_AI/tennis_unit_tests/PinInterface
TEST_DIR := /home/adamsl/SMOL_AI/tennis_unit_tests/PinInterface
BUILD_DIR := /home/adamsl/SMOL_AI/tennis_unit_tests/build/PinInterface

# Google Test and Google Mock directories
GTEST_DIR := /home/adamsl/SMOL_AI/tennis_unit_tests/googletest/build/lib
GMOCK_DIR := /home/adamsl/SMOL_AI/tennis_unit_tests/googletest/build/lib

# Object files and dependencies
TEST_OBJ := $(BUILD_DIR)/PinInterfaceTest.o
DEPS := $(GTEST_DIR)/libgtest_main.a $(GMOCK_DIR)/libgmock_main.a

# Main target (unit tests)
TARGET := $(BUILD_DIR)/PinInterfaceTest

# Targets
.PHONY: all clean

all: $(TARGET)

# Build the unit test executable
$(TARGET): $(TEST_OBJ) $(DEPS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile the unit test source file
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Google Test and Google Mock dependencies
$(GTEST_DIR)/libgtest_main.a:
	# Build Google Test if needed

$(GMOCK_DIR)/libgmock_main.a:
	# Build Google Mock if needed

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
