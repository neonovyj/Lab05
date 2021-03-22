// Copyright 2021 ivan <ikhonyak@gmail.com>
#include <gtest/gtest.h>

#include <FStack.hpp>
#include <Sstack.hpp>

int getNum() { return 4; }

TEST(FStack, testMove) {
  EXPECT_TRUE(std::is_move_constructible<FStack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<FStack<int>>::value);
}

TEST(FStack, testCopy) {
  EXPECT_FALSE(std::is_copy_constructible<FStack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<FStack<int>>::value);
}

TEST(Sstack, testMove) {
  EXPECT_TRUE(std::is_move_constructible<Sstack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Sstack<int>>::value);
}

TEST(Sstack, testCopy) {
  EXPECT_FALSE(std::is_copy_constructible<Sstack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Sstack<int>>::value);
}

TEST(FStack, testSize) {
  FStack<int> stackSize;
  for (int i = 0; i < 10; ++i) stackSize.push(i);
  EXPECT_EQ(stackSize.size(), 10);
}

TEST(FStack, testEmpty) {
  FStack<int> emptyStack;
  EXPECT_EQ(emptyStack.empty(), true);
}

TEST(FStack, testHead) {
  FStack<int> stackHead;
  stackHead.push(4);
  EXPECT_EQ(stackHead.head(), 4);
}

TEST(FStack, testThrowEmpty) {
  FStack<int> emptyStack;
  EXPECT_THROW(emptyStack.head(), std::out_of_range);
}

TEST(FStack, testMove1) {
  FStack<int> stackR;
  stackR.push(getNum());
  stackR.push(getNum());
  EXPECT_EQ(stackR.head(), 4);
}

TEST(FStack, testThrow) {
  FStack<int> stackThrow;
  EXPECT_THROW(stackThrow.pop(), std::out_of_range);
}
