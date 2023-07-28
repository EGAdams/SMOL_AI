#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Mode1Score.h"

class MockPlayer : public Player {
public:
    MockPlayer(GameState* gameState, int player_number) : Player(gameState, player_number) {}
    MOCK_METHOD(void, setOpponent, (IPlayer* opponent), (override));
    MOCK_METHOD(IPlayer*, getOpponent, (), (override));
    MOCK_METHOD(void, setPoints, (int points), (override));
    MOCK_METHOD(int, getPoints, (), (override));
    MOCK_METHOD(void, setGames, (int games), (override));
    MOCK_METHOD(int, getGames, (), (override));
    MOCK_METHOD(void, setMatches, (int matches), (override));
    MOCK_METHOD(int, getMatches, (), (override));
    MOCK_METHOD(void, setMode, (int mode), (override));
    MOCK_METHOD(int, getMode, (), (override));
    MOCK_METHOD(void, setSetting, (int setting), (override));
    MOCK_METHOD(int, getSetting, (), (override)); 
    MOCK_METHOD(void, setSets, ( IGameState* state, int sets), (override));
    MOCK_METHOD(int, getSets, (), (override));
    MOCK_METHOD(void, setSetHistory, (int set, int score), (override));
    // MOCK_METHOD(std::map<int, int>, getPlayer1SetHistory, (), (override));
    // MOCK_METHOD(std::map<int, int>, getPlayer2SetHistory, (), (override));
    MOCK_METHOD(int, incrementSetting, (), (override));
    MOCK_METHOD(int, number, (), (override));
};


class MockPinInterface : public PinInterface {
public:
    // Mock methods...
};

class MockGameState : public GameState {
public:
    MOCK_METHOD(int, getServeSwitch, (), (override));
    MOCK_METHOD(void, setServeSwitch, (int), (override));
    MOCK_METHOD(int, getUpdateDisplayDelay, (), (override));
    MOCK_METHOD(int, getTieBreak, (), (override));
    MOCK_METHOD(void, setTieBreak, (int), (override));
    MOCK_METHOD(int, getSetTieBreak, (), (override));
    MOCK_METHOD(void, setSetTieBreak, (int), (override));
    MOCK_METHOD(int, getPointFlash, (), (override));
    MOCK_METHOD(void, setPointFlash, (int), (override));
    MOCK_METHOD( unsigned long, getPreviousTime, (), (override));
    MOCK_METHOD(void, setPreviousTime, ( unsigned long ), (override));
    MOCK_METHOD(int, getToggle, (), (override));
    MOCK_METHOD(void, setToggle, (int), (override));
};

class MockHistory : public History {
public:
    // Mock methods...
};

class Mode1ScoreTest : public ::testing::Test {
protected:
    MockPlayer player1, player2;
    MockPinInterface pinInterface;
    MockGameState gameState;
    MockHistory history;
    Mode1Score* mode1Score;

    void SetUp() override {
        mode1Score = new Mode1Score(&player1, &player2, &pinInterface, &gameState, &history);
    }

    void TearDown() override {
        delete mode1Score;
    }
};

TEST(Mode1ScoreTest, Mode1P1ScoreTest) {
    // Create a Mode1Score object
    Mode1Score mode1Score;

    // Set player 1 score to 2
    mode1Score.player1.setScore(2);

    // Call the mode1P1Score method
    mode1Score.mode1P1Score();

    // Check that the score has been updated correctly
    ASSERT_EQ(mode1Score.player1.getScore(), 3);
}

TEST_F(Mode1ScoreTest, TestMode1P1Score_LessThan3Points) {
    // Arrange
    EXPECT_CALL(player1, getPoints()).WillOnce(::testing::Return(2));

    // Act
    mode1Score->mode1P1Score();

    // Assert
    // Assertions are made in the EXPECT_CALL statements
}

TEST_F(Mode1ScoreTest, TestMode1P1Score_3Points_LessThan3PointsP2) {
    // Arrange
    EXPECT_CALL(player1, getPoints()).WillOnce(::testing::Return(3));
    EXPECT_CALL(player2, getPoints()).WillOnce(::testing::Return(2));

    // Act
    mode1Score->mode1P1Score();

    // Assert
    // Assertions are made in the EXPECT_CALL statements
}

TEST_F(Mode1ScoreTest, TestMode1P1Score_3Points_EqualPoints) {
    // Arrange
    EXPECT_CALL(player1, getPoints()).WillOnce(::testing::Return(3));
    EXPECT_CALL(player2, getPoints()).WillOnce(::testing::Return(3));
    EXPECT_CALL(player1, setPoints(3)).Times(1);
    EXPECT_CALL(player2, setPoints(3)).Times(1);

    // Act
    mode1Score->mode1P1Score();

    // Assert
    // Assertions are made in the EXPECT_CALL statements
}

TEST_F(Mode1ScoreTest, TestMode1P1Score_MoreThan3Points_DifferenceMoreThan1) {
    // Arrange
    EXPECT_CALL(player1, getPoints()).WillOnce(::testing::Return(5));
    EXPECT_CALL(player2, getPoints()).WillOnce(::testing::Return(3));
    EXPECT_CALL(player1, getGames()).WillOnce(::testing::Return(1));
    EXPECT_CALL(player1, setGames(2)).Times(1);

    // Act
    mode1Score->mode1P1Score();

    // Assert
    // Assertions are made in the EXPECT_CALL statements
}

TEST_F(Mode1ScoreTest, TestMode1P1Score_4Points) {
    // Arrange
    EXPECT_CALL(player1, getPoints()).WillOnce(::testing::Return(4));
    EXPECT_CALL(gameState, setPointFlash(1)).Times(1);
    EXPECT_CALL(gameState, setToggle(0)).Times(1);

    // Act
    mode1Score->mode1P1Score();

    // Assert
    // Assertions are made in the EXPECT_CALL statements
}
