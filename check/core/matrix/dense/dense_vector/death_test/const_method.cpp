#include "../death_test.hpp"


TYPED_TEST(DenseVectorDeathTest_Size8_Stride1, ConstMethod) {
  const auto len    = this->len_;
  const auto vec    = this->vec_;;

  EXPECT_DEATH(vec(-1), "");
  EXPECT_DEATH(vec(len), "");

  EXPECT_DEATH(vec.find(-1), "");
  EXPECT_DEATH(vec.find(len), "");

  EXPECT_DEATH(vec({-1, 0}), "");
  EXPECT_DEATH(vec({0, len+1}), "");
  EXPECT_DEATH(vec({1, 0}), "");
}


TYPED_TEST(DenseVectorDeathTest_Size8_Stride3, ConstMethod) {
  const auto len    = this->len_;
  const auto vec    = this->vec_;;

  EXPECT_DEATH(vec(-1), "");
  EXPECT_DEATH(vec(len), "");

  EXPECT_DEATH(vec.find(-1), "");
  EXPECT_DEATH(vec.find(len), "");

  EXPECT_DEATH(vec({-1, 0}), "");
  EXPECT_DEATH(vec({0, len+1}), "");
  EXPECT_DEATH(vec({1, 0}), "");
}
