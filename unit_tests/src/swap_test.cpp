#include <gtest/gtest.h>
#include <swap.cpp>


TEST(swap, get_swaps_WRONG_PATH) {
  EXPECT_ANY_THROW(get_swaps("wrong path"));
}

TEST(swap, get_swaps_RIGHT_PATH) {
  EXPECT_NO_THROW(get_swaps(SWAPS_PATH));
}