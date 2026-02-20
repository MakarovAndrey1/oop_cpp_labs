#include <gtest/gtest.h>
#include "../include/time_converter.h"

TEST(ConvertTo24Hour, Midnight) {
    EXPECT_EQ(convertTo24Hour(12, 0, "am"), "0000");
}

TEST(ConvertTo24Hour, Noon) {
    EXPECT_EQ(convertTo24Hour(12, 0, "pm"), "1200");
}

TEST(ConvertTo24Hour, OneAm) {
    EXPECT_EQ(convertTo24Hour(1, 15, "am"), "0115");
}

TEST(ConvertTo24Hour, OnePm) {
    EXPECT_EQ(convertTo24Hour(1, 15, "pm"), "1315");
}

TEST(ConvertTo24Hour, ElevenAm) {
    EXPECT_EQ(convertTo24Hour(11, 59, "am"), "1159");
}

TEST(ConvertTo24Hour, ElevenPm) {
    EXPECT_EQ(convertTo24Hour(11, 59, "pm"), "2359");
}

TEST(ConvertTo24Hour, TwelveFifteenAm) {
    EXPECT_EQ(convertTo24Hour(12, 15, "am"), "0015");
}

TEST(ConvertTo24Hour, TwelveFifteenPm) {
    EXPECT_EQ(convertTo24Hour(12, 15, "pm"), "1215");
}

TEST(ConvertTo24Hour, SixAm) {
    EXPECT_EQ(convertTo24Hour(6, 0, "am"), "0600");
}

TEST(ConvertTo24Hour, SixPm) {
    EXPECT_EQ(convertTo24Hour(6, 0, "pm"), "1800");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}