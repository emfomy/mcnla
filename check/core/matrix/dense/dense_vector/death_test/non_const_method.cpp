#include "../death_test.hpp"


TYPED_TEST(DenseVectorDeathTest_Size8_Stride1, NonConstMethod) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto len = this->len_;
  auto vec = const_cast<VectorType&>(this->vec_);

  EXPECT_DEATH(vec.resize(-1), "");
  EXPECT_DEATH(vec.resize(len+1), "");
}


TYPED_TEST(DenseVectorDeathTest_Size8_Stride3, NonConstMethod) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto len = this->len_;
  auto vec = const_cast<VectorType&>(this->vec_);

  EXPECT_DEATH(vec.resize(-1), "");
  EXPECT_DEATH(vec.resize(len+1), "");
}
