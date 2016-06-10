#include <gtest/gtest.h>
#include <hdd.cpp>


TEST(hdd, get_partitions_WRONG_PATH) {
  EXPECT_ANY_THROW(get_partitions("wrong path"));
}

TEST(hdd, get_partitions_RIGHT_PATH) {
  EXPECT_NO_THROW(get_partitions(PARTITIONS_PATH));
}

//TEST(hdd, start_RETURN_VALUE) {
//  EXPECT_EQ(0, start());
//}
