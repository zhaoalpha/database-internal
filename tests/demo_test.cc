//
// Created by zhao on 23-4-19.
//
#include "../src/include/demo/demo.h"
#include <gtest/gtest.h>

TEST(demoTest, sampleTest) {
  int result = Add(3, 5);
  int expected = 8;
  EXPECT_EQ(expected, result);
}