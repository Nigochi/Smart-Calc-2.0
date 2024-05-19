#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>

#include "../model/model.h"
#include <string.h>

#define ERROR_RATE 0.00001

using namespace s21;

TEST(CalculateTest, Test1) {
  s21::Model model;
  std::string str = "2 + 2";
  double result = 0;
  double expectedResult = 4;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}

TEST(CalculateTest, Test2) {
  s21::Model model;
  std::string str = "2 - 2";
  double result = 0;
  double expectedResult = 0;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}


TEST(CalculateTest, Test3) {
  s21::Model model;
  std::string str =
      "cos(4) * (8 * 4 - (56 + 7 * sin(85 / 10) / (-6 * (+1 - 2)-1)-1)-1)";
  double result = 0;
  double expectedResult = 16.41814;
  model.startCalc(&str, &result);;
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}
 

TEST(CalculateTest, Test4) {
  s21::Model model;
  std::string str = "tan(8)-atan(sqrt(5))";
  double result = 0;
  double expectedResult = -7.94997;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}
 

TEST(CalculateTest, Test5) {
  s21::Model model;
  std::string str = "-ln(log(78))-(-tan(45))";
  double result = 0;
  double expectedResult = 0.98209;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}
 

TEST(CalculateTest, Test6) {
  s21::Model model;
  std::string str = "-ln(log(78))-(-tan(45)))";
  double result = 0;
  double expectedResult = 0;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}
 

TEST(CalculateTest, Test7) {
  s21::Model model;
  std::string str = "-ln(log(7.8))-(-tan(45)))";
  double result = 0;
  double expectedResult = 0;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}
 ;

TEST(CalculateTest, Test8) {
  s21::Model model;
  std::string str = "-ln(log(7.8.))-(-tan(45)))";
  double result = 0;
  double expectedResult = 0;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}

TEST(CalculateTest, Test9) {
  s21::Model model;
  std::string str = "+ 5 - 4 mod 5";
  double result = 0;
  double expectedResult = 1;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}
 
TEST(CalculateTest, Test10) {
  s21::Model model;
  std::string str = "2^3 + 4 * acos(0.123) - asin(0)\0";
  double result = 0;
  double expectedResult = 13.78994;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}


TEST(CalculateTest, Test11) {
  s21::Model model;
  std::string str = "0-+7";
  double result = 0;
  double expectedResult = 7;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}
 

TEST(CalculateTest, Test12) {
  s21::Model model;
  std::string str = "-ln(jjjlog(7.8.))-(-tan(45)))";
  double result = 0;
  double expectedResult = 0;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}
 

TEST(CalculateTest, Test13) {
  s21::Model model;
  std::string str = "-tan(45)*tan(45)";
  double result = 0;
  double expectedResult = -2.62367;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}
 

TEST(CalculateTest, Test14) {
  s21::Model model;
  std::string str = "-3+7-";
  double result = 0;
  double expectedResult = 0;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}
 

TEST(CalculateTest, Test15) {
  s21::Model model;
  std::string str = "8(7)";
  double result = 0;
  double expectedResult = 0;
  model.startCalc(&str, &result);
  EXPECT_NEAR(result, expectedResult, ERROR_RATE);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
