# Variable definitions
GTEST_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib
GMOCK_DIR := /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib


CXX = g++
CXXFLAGS = -Wall -Wextra -g -I$(GTEST_DIR)/include
LDFLAGS = -L$(GTEST_DIR)/lib -lgtest -lgmock -lgtest_main -pthread
TARGET = run_tests

# Define our source and object files
SOURCES = PinInterface.cpp PinInterfaceTest.cpp     \
		  ../PinState/PinState.cpp					\
		  ../TranslateConstant/TranslateConstant.cpp

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
