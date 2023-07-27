To run the Mode1ScoreTest in this directory, you need to modify the Makefile to include the necessary changes. Here's how you can do it:

1. Open the Makefile in a text editor.
2. Add the following lines at the end of the file:

```make
# Mode1ScoreTest
Mode1ScoreTest: Mode1ScoreTest.o $(TEST_OBJECTS)
    $(CXX) $^ -o $@ $(LDFLAGS)

Mode1ScoreTest.o: Mode1ScoreTest.cpp
    $(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<
```

3. Save the Makefile.

To compile and run the Mode1ScoreTest, open a terminal and navigate to the directory containing the Makefile. Then run the following command:

```bash
make Mode1ScoreTest
```

This will compile the test and generate an executable called "Mode1ScoreTest". To run the test, execute the following command:

```bash
./Mode1ScoreTest
```

This will execute the test and display the test results.

Note: Make sure you have the necessary dependencies installed, such as Google Test, before running the test.

like this is important for example:
``` make 
# this one threw me off for a while
GTEST_DIR=/home/adamsl/rpi-rgb-led-matrix/tennis-game
```