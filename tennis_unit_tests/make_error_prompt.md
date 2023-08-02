I am getting the following error when running:
``` command
    make all
```

``` error
g++   -std=c++14 -Wall -Wextra -g    Mode1ScoreTest.cpp   -o Mode1ScoreTest
In file included from ../GameLeds/../ScoreBoard/../NumberDrawer/../../include/led-matrix.h:31,
                 from ../GameLeds/../ScoreBoard/../NumberDrawer/NumberDrawer.h:4,
                 from ../GameLeds/../ScoreBoard/ScoreBoard.h:7,
                 from ../GameLeds/GameLeds.h:8,
                 from Mode1Score.h:5,
                 from Mode1ScoreTest.cpp:3:
../GameLeds/../ScoreBoard/../NumberDrawer/../../include/pixel-mapper.h: In member function ‘virtual bool rgb_matrix::PixelMapper::SetParameters(int, int, const char*)’:
../GameLeds/../ScoreBoard/../NumberDrawer/../../include/pixel-mapper.h:51:34: warning: unused parameter ‘chain’ [-Wunused-parameter]
   51 |   virtual bool SetParameters(int chain, int parallel,
      |                              ~~~~^~~~~
../GameLeds/../ScoreBoard/../NumberDrawer/../../include/pixel-mapper.h:51:45: warning: unused parameter ‘parallel’ [-Wunused-parameter]
   51 |   virtual bool SetParameters(int chain, int parallel,
      |                                         ~~~~^~~~~~~~
../GameLeds/../ScoreBoard/../NumberDrawer/../../include/pixel-mapper.h:52:42: warning: unused parameter ‘parameter_string’ [-Wunused-parameter]
   52 |                              const char *parameter_string) {
      |                              ~~~~~~~~~~~~^~~~~~~~~~~~~~~~
Mode1ScoreTest.cpp: In member function ‘virtual void Mode1ScoreTest_Mode1P1ScoreTest_Test::TestBody()’:
Mode1ScoreTest.cpp:83:5: error: ‘mode1Score’ was not declared in this scope; did you mean ‘Mode1Score’?
   83 |     mode1Score.player1.setScore(2);
      |     ^~~~~~~~~~
      |     Mode1Score
In file included from /usr/local/include/gtest/gtest-printers.h:115,
                 from /usr/local/include/gtest/gtest-matchers.h:49,
                 from /usr/local/include/gtest/internal/gtest-death-test-internal.h:47,
                 from /usr/local/include/gtest/gtest-death-test.h:43,
                 from /usr/local/include/gtest/gtest.h:65,
                 from Mode1ScoreTest.cpp:1:
/usr/local/include/gtest/internal/gtest-internal.h: In instantiation of ‘testing::Test* testing::internal::TestFactoryImpl<TestClass>::CreateTest() [with TestClass = Mode1ScoreTest_TestMode1P1Score_4Points_Test]’:
/usr/local/include/gtest/internal/gtest-internal.h:457:9:   required from here
/usr/local/include/gtest/internal/gtest-internal.h:457:40: error: use of deleted function ‘Mode1ScoreTest_TestMode1P1Score_4Points_Test::Mode1ScoreTest_TestMode1P1Score_4Points_Test()’
  457 |   Test* CreateTest() override { return new TestClass; }
      |                                        ^~~~~~~~~~~~~
Mode1ScoreTest.cpp:143:8: note: ‘Mode1ScoreTest_TestMode1P1Score_4Points_Test::Mode1ScoreTest_TestMode1P1Score_4Points_Test()’ is implicitly deleted because the default definition would be ill-formed:
  143 | TEST_F(Mode1ScoreTest, TestMode1P1Score_4Points) {
      |        ^~~~~~~~~~~~~~
Mode1ScoreTest.cpp:143:8: error: use of deleted function ‘Mode1ScoreTest::Mode1ScoreTest()’
Mode1ScoreTest.cpp:57:7: note: ‘Mode1ScoreTest::Mode1ScoreTest()’ is implicitly deleted because the default definition would be ill-formed:
   57 | class Mode1ScoreTest : public ::testing::Test {
      |       ^~~~~~~~~~~~~~
Mode1ScoreTest.cpp:57:7: error: no matching function for call to ‘MockPlayer::MockPlayer()’
Mode1ScoreTest.cpp:7:5: note: candidate: ‘MockPlayer::MockPlayer(GameState*, int)’
    7 |     MockPlayer(GameState* gameState, int player_number) : Player(gameState, player_number) {}
      |     ^~~~~~~~~~
Mode1ScoreTest.cpp:7:5: note:   candidate expects 2 arguments, 0 provided
Mode1ScoreTest.cpp:57:7: error: no matching function for call to ‘MockPlayer::MockPlayer()’
   57 | class Mode1ScoreTest : public ::testing::Test {
      |       ^~~~~~~~~~~~~~
Mode1ScoreTest.cpp:7:5: note: candidate: ‘MockPlayer::MockPlayer(GameState*, int)’
    7 |     MockPlayer(GameState* gameState, int player_number) : Player(gameState, player_number) {}
      |     ^~~~~~~~~~
Mode1ScoreTest.cpp:7:5: note:   candidate expects 2 arguments, 0 provided
Mode1ScoreTest.cpp:57:7: error: use of deleted function ‘MockPinInterface::MockPinInterface()’
   57 | class Mode1ScoreTest : public ::testing::Test {
      |       ^~~~~~~~~~~~~~
Mode1ScoreTest.cpp:30:7: note: ‘MockPinInterface::MockPinInterface()’ is implicitly deleted because the default definition would be ill-formed:
   30 | class MockPinInterface : public PinInterface {
      |       ^~~~~~~~~~~~~~~~
Mode1ScoreTest.cpp:30:7: error: no matching function for call to ‘PinInterface::PinInterface()’
In file included from ../GameLeds/GameLeds.h:4,
                 from Mode1Score.h:5,
                 from Mode1ScoreTest.cpp:3:
../GameLeds/../PinInterface/PinInterface.h:10:5: note: candidate: ‘PinInterface::PinInterface(PinState*)’
   10 |     PinInterface(PinState* pinState);
      |     ^~~~~~~~~~~~
../GameLeds/../PinInterface/PinInterface.h:10:5: note:   candidate expects 1 argument, 0 provided
../GameLeds/../PinInterface/PinInterface.h:8:7: note: candidate: ‘PinInterface::PinInterface(const PinInterface&)’
    8 | class PinInterface {
      |       ^~~~~~~~~~~~
../GameLeds/../PinInterface/PinInterface.h:8:7: note:   candidate expects 1 argument, 0 provided
In file included from /usr/local/include/gtest/gtest-printers.h:115,
                 from /usr/local/include/gtest/gtest-matchers.h:49,
                 from /usr/local/include/gtest/internal/gtest-death-test-internal.h:47,
                 from /usr/local/include/gtest/gtest-death-test.h:43,
                 from /usr/local/include/gtest/gtest.h:65,
                 from Mode1ScoreTest.cpp:1:
/usr/local/include/gtest/internal/gtest-internal.h: In instantiation of ‘testing::Test* testing::internal::TestFactoryImpl<TestClass>::CreateTest() [with TestClass = Mode1ScoreTest_TestMode1P1Score_MoreThan3Points_DifferenceMoreThan1_Test]’:
/usr/local/include/gtest/internal/gtest-internal.h:457:9:   required from here
/usr/local/include/gtest/internal/gtest-internal.h:457:40: error: use of deleted function ‘Mode1ScoreTest_TestMode1P1Score_MoreThan3Points_DifferenceMoreThan1_Test::Mode1ScoreTest_TestMode1P1Score_MoreThan3Points_DifferenceMoreThan1_Test()’
  457 |   Test* CreateTest() override { return new TestClass; }
      |                                        ^~~~~~~~~~~~~
Mode1ScoreTest.cpp:129:8: note: ‘Mode1ScoreTest_TestMode1P1Score_MoreThan3Points_DifferenceMoreThan1_Test::Mode1ScoreTest_TestMode1P1Score_MoreThan3Points_DifferenceMoreThan1_Test()’ is implicitly deleted because the default definition would be ill-formed:
  129 | TEST_F(Mode1ScoreTest, TestMode1P1Score_MoreThan3Points_DifferenceMoreThan1) {
      |        ^~~~~~~~~~~~~~
Mode1ScoreTest.cpp:129:8: error: use of deleted function ‘Mode1ScoreTest::Mode1ScoreTest()’
/usr/local/include/gtest/internal/gtest-internal.h: In instantiation of ‘testing::Test* testing::internal::TestFactoryImpl<TestClass>::CreateTest() [with TestClass = Mode1ScoreTest_TestMode1P1Score_3Points_EqualPoints_Test]’:
/usr/local/include/gtest/internal/gtest-internal.h:457:9:   required from here
/usr/local/include/gtest/internal/gtest-internal.h:457:40: error: use of deleted function ‘Mode1ScoreTest_TestMode1P1Score_3Points_EqualPoints_Test::Mode1ScoreTest_TestMode1P1Score_3Points_EqualPoints_Test()’
  457 |   Test* CreateTest() override { return new TestClass; }
      |                                        ^~~~~~~~~~~~~
Mode1ScoreTest.cpp:115:8: note: ‘Mode1ScoreTest_TestMode1P1Score_3Points_EqualPoints_Test::Mode1ScoreTest_TestMode1P1Score_3Points_EqualPoints_Test()’ is implicitly deleted because the default definition would be ill-formed:
  115 | TEST_F(Mode1ScoreTest, TestMode1P1Score_3Points_EqualPoints) {
      |        ^~~~~~~~~~~~~~
Mode1ScoreTest.cpp:115:8: error: use of deleted function ‘Mode1ScoreTest::Mode1ScoreTest()’
/usr/local/include/gtest/internal/gtest-internal.h: In instantiation of ‘testing::Test* testing::internal::TestFactoryImpl<TestClass>::CreateTest() [with TestClass = Mode1ScoreTest_TestMode1P1Score_3Points_LessThan3PointsP2_Test]’:
/usr/local/include/gtest/internal/gtest-internal.h:457:9:   required from here
/usr/local/include/gtest/internal/gtest-internal.h:457:40: error: use of deleted function ‘Mode1ScoreTest_TestMode1P1Score_3Points_LessThan3PointsP2_Test::Mode1ScoreTest_TestMode1P1Score_3Points_LessThan3PointsP2_Test()’
  457 |   Test* CreateTest() override { return new TestClass; }
      |                                        ^~~~~~~~~~~~~
Mode1ScoreTest.cpp:103:8: note: ‘Mode1ScoreTest_TestMode1P1Score_3Points_LessThan3PointsP2_Test::Mode1ScoreTest_TestMode1P1Score_3Points_LessThan3PointsP2_Test()’ is implicitly deleted because the default definition would be ill-formed:
  103 | TEST_F(Mode1ScoreTest, TestMode1P1Score_3Points_LessThan3PointsP2) {
      |        ^~~~~~~~~~~~~~
Mode1ScoreTest.cpp:103:8: error: use of deleted function ‘Mode1ScoreTest::Mode1ScoreTest()’
/usr/local/include/gtest/internal/gtest-internal.h: In instantiation of ‘testing::Test* testing::internal::TestFactoryImpl<TestClass>::CreateTest() [with TestClass = Mode1ScoreTest_TestMode1P1Score_LessThan3Points_Test]’:
/usr/local/include/gtest/internal/gtest-internal.h:457:9:   required from here
/usr/local/include/gtest/internal/gtest-internal.h:457:40: error: use of deleted function ‘Mode1ScoreTest_TestMode1P1Score_LessThan3Points_Test::Mode1ScoreTest_TestMode1P1Score_LessThan3Points_Test()’
  457 |   Test* CreateTest() override { return new TestClass; }
      |                                        ^~~~~~~~~~~~~
Mode1ScoreTest.cpp:92:8: note: ‘Mode1ScoreTest_TestMode1P1Score_LessThan3Points_Test::Mode1ScoreTest_TestMode1P1Score_LessThan3Points_Test()’ is implicitly deleted because the default definition would be ill-formed:
   92 | TEST_F(Mode1ScoreTest, TestMode1P1Score_LessThan3Points) {
      |        ^~~~~~~~~~~~~~
Mode1ScoreTest.cpp:92:8: error: use of deleted function ‘Mode1ScoreTest::Mode1ScoreTest()’
make: *** [<builtin>: Mode1ScoreTest] Error 1
```