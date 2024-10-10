#include <gtest/gtest.h>
#include "bitarray.h"

TEST(InitTests, Constructors) {
 BitArray bits1(10, 0);
 BitArray bits2(10, 1);
 BitArray bits3 = bits1;
 EXPECT_FALSE(bits1 == bits2);
 EXPECT_TRUE(bits1 == bits3);
}

TEST(InitTests, Set) {
 BitArray bits1(5, false);
 bits1.set(2, true);
 EXPECT_TRUE(bits1[2]);
 EXPECT_FALSE(bits1[1]);
}

TEST(InitTests, Reset) {
 BitArray bits1(5,  true);
 bits1.reset();
 EXPECT_FALSE(bits1[1]);
 EXPECT_FALSE(bits1[3]);
}

TEST(InitTests, IncorrectTest) {
 BitArray bits1(5, true);
 bits1.reset(1);
 EXPECT_FALSE(bits1[3]);
 EXPECT_TRUE(bits1[1]);
}

TEST(ArraySize, Push) {
 BitArray bits1(5, false);
 bits1.push_back(true);
 EXPECT_TRUE(bits1[0]);
 bits1.push_back(false);
 bits1.push_back(true);
 EXPECT_TRUE(bits1[2]);
}

TEST(ArraySize, Resize) {
 BitArray bits1(5);
 EXPECT_STREQ(bits1.to_string().c_str(), "00000");
 bits1.resize(7, true);
 EXPECT_STREQ(bits1.to_string().c_str(), "0000011");
}

TEST(ArraySize, Reset) {
 BitArray bits1(5);
 bits1.push_back(true);
 bits1.push_back(true);
 bits1.reset();
 bits1.push_back(true);
 EXPECT_TRUE(bits1[0]);
 EXPECT_FALSE(bits1[1]);
}

TEST(ArraySize, IncorrectTest) {
 BitArray bits1(5);
 bits1.push_back(false);
 bits1.push_back(true);
 EXPECT_TRUE(bits1[0]);
}

TEST(BitOps, Logic_OR) {
 BitArray bits1(5);
 BitArray bits2(5);
 bits1.set(2);
 bits2.set(4);
 BitArray bits3 = bits1 | bits2;
 EXPECT_STREQ(bits3.to_string().c_str(), "00101");
}

TEST(BitOps, Logic_AND) {
 BitArray bits1(5);
 BitArray bits2(5);
 bits1.set(2);
 bits2.set(4);
 bits2.set(2);
 BitArray bits3 = bits1 & bits2;
 EXPECT_STREQ(bits3.to_string().c_str(), "00100");
}

TEST(BitOps, Logic_NOT) {
 BitArray bits1(5);
 bits1.set(3);
 EXPECT_STREQ((~bits1).to_string().c_str(), "11101");
}

TEST(BitOps, Logic_Shift) {
 BitArray bits1(10);
 bits1.set(2);
 bits1 >>= 4;
 EXPECT_FALSE(bits1[2]);
 EXPECT_TRUE(bits1[6]);
}
