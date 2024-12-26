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

TEST(InitTests, ResetTwice) {
 BitArray bits1(5, true);
 bits1.set(1,true);
 bits1.set(3, true);
 bits1.reset();
 bits1.reset();
 EXPECT_FALSE(bits1[1]);
 EXPECT_FALSE(bits1[3]);
}

TEST(InitTest, AssignOperator) {
 BitArray bits1(7);
 BitArray bits2(7);
 bits1.set(4);
 bits1.set(5);
 bits2.set(1);
 bits2 = bits1;
 EXPECT_TRUE(bits2[4]);
 EXPECT_TRUE(bits2[5]);
 EXPECT_FALSE(bits2[1]);
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

TEST(BitOps, BitCount) {
 BitArray bits1(10);
 bits1.set(2);
 bits1.set(3);
 bits1.set(6);
 EXPECT_EQ(3, bits1.count());
}

TEST(BitOps, Any) {
 BitArray bits1(10);
 BitArray bits2(6);
 bits1.reset();
 EXPECT_FALSE(bits1.any());
 bits2.set(3);
 bits2.set(4);
 EXPECT_TRUE(bits2.any());
}

TEST(BitOps, None) {
 BitArray bits1(10);
 BitArray bits2(6);
 bits1.reset();
 EXPECT_TRUE(bits1.none());
 bits2.set(4);
 bits2.set(1);
 EXPECT_FALSE(bits2.none());
}

TEST(Other, Swap) {
 BitArray bits1(10);
 BitArray bits2(10);
 bits1.set(2);
 bits1.set(3);
 bits2.set(6);

 bits1.swap(bits2);

 EXPECT_TRUE(bits1[6]);
 EXPECT_TRUE(bits2[2]);
 EXPECT_TRUE(bits2[3]);

 EXPECT_FALSE(bits1[2]);
 EXPECT_FALSE(bits1[3]);
 EXPECT_FALSE(bits2[6]);
}

TEST(Other, SwapItself) {
 BitArray bits1(10);
 bits1.set(4);
 bits1.swap(bits1);
 EXPECT_TRUE(bits1[4]);
 EXPECT_FALSE(bits1[1]);
}

TEST(Other, Clear) {
 BitArray bits1(5,  true);
 bits1.set(1);
 bits1.set(2);
 bits1.reset();
 EXPECT_FALSE(bits1[1]);
 EXPECT_FALSE(bits1[2]);
 EXPECT_FALSE(bits1[3]);
}

