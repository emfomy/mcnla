#include "../death_test.hpp"


TYPED_TEST(DenseVectorDeathTest_Size8_Stride1, NonConstMethod) {
  using VectorType = mcnla::container::DenseVector<TypeParam>;

  const auto length = this->length_;
  const auto stride = this->stride_;
  auto vec = const_cast<VectorType&>(this->vec_);

  EXPECT_DEATH(vec.resize(-1, stride), "");
  EXPECT_DEATH(vec.resize(length, 0), "");
  EXPECT_DEATH(vec.resize(length+1, stride), "");
  EXPECT_DEATH(vec.resize(length, stride+1), "");
}


TYPED_TEST(DenseVectorDeathTest_Size8_Stride3, NonConstMethod) {
  using VectorType = mcnla::container::DenseVector<TypeParam>;

  const auto length = this->length_;
  const auto stride = this->stride_;
  auto vec = const_cast<VectorType&>(this->vec_);

  EXPECT_DEATH(vec.resize(-1, stride), "");
  EXPECT_DEATH(vec.resize(length, 0), "");
  EXPECT_DEATH(vec.resize(length+1, stride), "");
  EXPECT_DEATH(vec.resize(length, stride+1), "");
}
