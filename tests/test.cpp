// Copyright 2018 Your Name <your_email>

#include <moveStackNew.h>
#include <gtest/gtest.h>
#include <stack_n.h>

int getNum(){
  return 4;
}

TEST(moveStackNew, testMove){
  EXPECT_TRUE(std::is_move_constructible<moveStackNew<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<moveStackNew<int>>::value);
}

TEST(moveStackNew, testCopy){
  EXPECT_FALSE(std::is_copy_constructible<moveStackNew<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<moveStackNew<int>>::value);
}

TEST(stack_n, testMove){
  EXPECT_TRUE(std::is_move_constructible<stack_n<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<stack_n<int>>::value);
}

TEST(stack_n, testCopy){
  EXPECT_FALSE(std::is_copy_constructible<stack_n<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<stack_n<int>>::value);
}

TEST(moveStackNew, testSize){
  moveStackNew<int> stackSize;
  for (int i = 0; i < 10; ++i)
    stackSize.push(i);
  EXPECT_EQ(stackSize.size(), 10);
}

TEST(moveStackNew, testEmpty){
  moveStackNew<int> emptyStack;
  EXPECT_EQ(emptyStack.empty(), true);
}

TEST(moveStackNew, testHead){
  moveStackNew<int> stackHead;
  stackHead.push(4);
  EXPECT_EQ(stackHead.head(), 4);
}

TEST(moveStackNew, testThrowEmpty){
  moveStackNew<int> emptyStack;
  EXPECT_THROW(emptyStack.head(), std::out_of_range);
}

TEST(moveStackNew, testMove1){
  moveStackNew<int> stackR;
  stackR.push(getNum());
  stackR.push(getNum());
  EXPECT_EQ(stackR.head(), 4);
}

TEST(moveStackNew, testThrow){
  moveStackNew<int> stackThrow;
  EXPECT_THROW(stackThrow.pop(), std::out_of_range);
}
