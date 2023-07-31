# Compiler settings
CXX := g++
CXXFLAGS := -std=c++14 -Wall -Wextra

# Directories
SRC_DIR   := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface
TEST_DIR  := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface
BUILD_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/build/PinInterface

# Google Test and Google Mock directories
GTEST_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib
GMOCK_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib

# Object files and dependencies
TEST_OBJ := $(BUILD_DIR)/MockPinInterface.o
DEPS := $(GTEST_DIR)/libgtest.a $(GTEST_DIR)/libgtest_main.a $(GMOCK_DIR)/libgmock.a $(GMOCK_DIR)/libgmock_main.a


# Main target (unit tests)
TARGET := $(BUILD_DIR)/MockPinInterfaceTest

# Targets
.PHONY: all clean

all: $(TARGET)

# Build the unit test executable
$(TARGET): $(DEPS) $(TEST_OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile the unit test source file
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(GTEST_DIR)/libgtest_main.a:
	cd /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest && cmake .
	cd /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest && make

$(GMOCK_DIR)/libgmock_main.a:
	cd /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest && cmake .
	cd /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest && make

# Clean build artifacts
clean:
	find $(BUILD_DIR) -type f -name '*.o' -delete
	rm -f $(TARGET)
