#include <gtest/gtest.h>
#include "computer_information.cpp"


class computer_information_fixture : public ::testing::Test {

protected:
  virtual void TearDown() {
    delete info;
  }

  virtual void SetUp() {
    info = new computer_information;
  }

  computer_information *info;
};

TEST_F(computer_information_fixture, get_value_RIGHT_STRING) {
  EXPECT_STREQ("1", info->get_value("cpu model : 1").c_str());
}

TEST_F(computer_information_fixture, get_value_WRONG_STRING) {
  EXPECT_STRNE("1", info->get_value("cpu model : 1th very interesting").c_str());
}

TEST_F(computer_information_fixture, to_unsigned_POSITIVE_VALUE) {
  EXPECT_EQ(2, info->to_unsigned("2"));
}

TEST_F(computer_information_fixture, to_unsigned_NEGATIVE_VALUE){
  EXPECT_ANY_THROW(info->to_unsigned("-1"));
}

TEST_F(computer_information_fixture, to_unsigned_NOT_NUMBER) {
  EXPECT_ANY_THROW(info->to_unsigned("check"));
}