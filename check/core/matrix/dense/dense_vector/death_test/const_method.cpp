#include "../death_test.hpp"


TYPED_TEST(DenseVectorDeathTest_Size8_Stride1, ConstMethod) {
  const auto length = this->length_;
  const auto vec    = this->vec_;;

  EXPECT_DEATH(vec(-1), "");
  EXPECT_DEATH(vec(length), "");

  EXPECT_DEATH(vec.find(-1), "");
  EXPECT_DEATH(vec.find(length), "");

  EXPECT_DEATH(vec({-1, 0}), "");
  EXPECT_DEATH(vec({0, length+1}), "");
  EXPECT_DEATH(vec({1, 0}), "");
}


TYPED_TEST(DenseVectorDeathTest_Size8_Stride3, ConstMethod) {
  const auto length = this->length_;
  const auto vec    = this->vec_;;

  EXPECT_DEATH(vec(-1), "");
  EXPECT_DEATH(vec(length), "");

  EXPECT_DEATH(vec.find(-1), "");
  EXPECT_DEATH(vec.find(length), "");

  EXPECT_DEATH(vec({-1, 0}), "");
  EXPECT_DEATH(vec({0, length+1}), "");
  EXPECT_DEATH(vec({1, 0}), "");
}
