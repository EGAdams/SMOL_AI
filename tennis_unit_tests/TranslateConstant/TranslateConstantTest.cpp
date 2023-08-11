#include <gtest/gtest.h>
#include "TranslateConstant.h"

class TranslateConstantTest : public testing::Test {
protected:
    TranslateConstant* translator;

    void SetUp() override {
        translator = new TranslateConstant();
    }

    void TearDown() override {
        delete translator;
    }
};

TEST_F(TranslateConstantTest, TranslatesConstantsCorrectly) {
    EXPECT_EQ(translator->get_translated_constant(22), "P1_POINTS_LED1");
    EXPECT_EQ(translator->get_translated_constant(23), "P1_POINTS_LED2");
    EXPECT_EQ(translator->get_translated_constant(38), "RESET");
    EXPECT_EQ(translator->get_translated_constant(39), "UNDO");
    EXPECT_EQ(translator->get_translated_constant(202), "PLAYER_BUTTONS");
    EXPECT_EQ(translator->get_translated_constant(150), "ROTARY");
}

TEST_F(TranslateConstantTest, TranslatesDigitalModesCorrectly) {
    EXPECT_EQ(translator->get_translated_digital_mode(0), "LOW");
    EXPECT_EQ(translator->get_translated_digital_mode(1), "HIGH");
}
