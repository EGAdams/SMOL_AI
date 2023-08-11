#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Mode1Score.h"
#include "../History/IHistoryMock.h"
#include "../Player/IPlayerMock.h"
#include "../GameState/IGameStateMock.h"
#include "../PinInterface/IPinInterfaceMock.h"

class Mode1ScoreTest : public ::testing::Test
{
protected:
    IPlayerMock mockPlayer1;
    IPlayerMock mockPlayer2;
    IPinInterfaceMock mockPinInterface;
    IGameStateMock mockGameState;

    void SetUp() override {
        IPlayerMock mockPlayer2;
        IPinInterfaceMock mockPinInterface;  // Hypothetical mock object
        IGameStateMock mockGameState;       // Hypothetical mock object
        auto historyMock = std::make_shared<IHistoryMock>();
        mode1Score = std::make_shared<Mode1Score>( &mockPlayer1, &mockPlayer2, &mockPinInterface, &mockGameState, historyMock.get());
    }

    std::shared_ptr<Mode1Score> mode1Score;
};

TEST_F( Mode1ScoreTest, TestCalculateScore ) {
    // Replace this with your actual test
    // Here's an example:
    // EXPECT_EQ(mode1Score->calculateScore(), expectedScore);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(Mode1ScoreTest, UpdateScoreIncreasesPlayerScore) {
    EXPECT_CALL(mockPlayer1, getPoints()).WillOnce(testing::Return(2));
    EXPECT_CALL(mockPlayer1, setPoints(3));

    mode1Score->updateScore(&mockPlayer1);
}

// TEST_F(Mode1ScoreTest, TestUpdateScore) {
//     IPlayerMock mockPlayer; // Create a mock player  
//     EXPECT_CALL(mockPlayer, getHistory()).Times(1); // Set expectations on the mock player
//     mode1Score->updateScore(&mockPlayer); } // Call the method under test