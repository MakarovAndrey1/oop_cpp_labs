#include <gtest/gtest.h>
#include "../include/Hex.h"

TEST(HexTest, DefaultConstructor) {
    Hex hex;
    EXPECT_EQ(hex.getSize(), 1);
    EXPECT_EQ(hex.toString(), "0");
}

TEST(HexTest, SizeValueConstructor) {
    Hex hex(3, 10); // "AAA"
    EXPECT_EQ(hex.toString(), "AAA");
    
    Hex hex2(1, 15); // "F"
    EXPECT_EQ(hex2.toString(), "F");
}

TEST(HexTest, InitializerListConstructor) {
    Hex hex{1, 10, 15}; // "FA1"
    EXPECT_EQ(hex.toString(), "FA1");
}

TEST(HexTest, StringConstructor) {
    Hex hex("1A3F");
    EXPECT_EQ(hex.toString(), "1A3F");
    
    Hex hex2("0");
    EXPECT_EQ(hex2.toString(), "0");
}

TEST(HexTest, CopyConstructor) {
    Hex original("ABC");
    Hex copy(original);
    EXPECT_TRUE(original.equals(copy));
}

TEST(HexTest, MoveConstructor) {
    Hex original("123");
    Hex moved(std::move(original));
    EXPECT_EQ(moved.toString(), "123");
    EXPECT_EQ(original.getSize(), 0);
}

TEST(HexTest, Addition) {
    Hex a("1A");
    Hex b("F");
    Hex result = a.add(b);
    EXPECT_EQ(result.toString(), "29"); // 26 + 15 = 41 = 0x29
    
    Hex c("FF");
    Hex d("1");
    Hex result2 = c.add(d);
    EXPECT_EQ(result2.toString(), "100");
}

TEST(HexTest, Subtraction) {
    Hex a("29");
    Hex b("F");
    Hex result = a.subtract(b);
    EXPECT_EQ(result.toString(), "1A"); // 41 - 15 = 26 = 0x1A
    
    Hex c("100");
    Hex d("1");
    Hex result2 = c.subtract(d);
    EXPECT_EQ(result2.toString(), "FF");
}

TEST(HexTest, Comparison) {
    Hex a("A");
    Hex b("B");
    Hex c("A");
    
    EXPECT_TRUE(a.lessThan(b));
    EXPECT_TRUE(b.greaterThan(a));
    EXPECT_TRUE(a.equals(c));
    EXPECT_FALSE(a.equals(b));
}

TEST(HexTest, Normalization) {
    Hex hex(5, 0); // "00000" -> "0"
    EXPECT_EQ(hex.getSize(), 1);
    EXPECT_EQ(hex.toString(), "0");
    
    Hex hex2{0, 0, 1, 0}; // "0100" -> "100"
    EXPECT_EQ(hex2.toString(), "100");
}

TEST(HexTest, AssignOperations) {
    Hex a("10");
    Hex b("5");
    Hex result = a.addAssign(b);
    EXPECT_EQ(result.toString(), "15");
    
    Hex result2 = a.subtractAssign(b);
    EXPECT_EQ(result2.toString(), "B");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
