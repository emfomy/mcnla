#undef MCNLA_USE_GTEST
#include "../test.hpp"
#include <queue>

TYPED_TEST(DenseVectorDeathTest, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;
  using ArrayType  = mcnla::matrix::Array<TypeParam>;
  EXPECT_DEATH({VectorType vec(8, 0);}, "");
  EXPECT_DEATH({VectorType vec(8, 3, 21);}, "");
  EXPECT_DEATH({ArrayType array(25, 4); VectorType vec(8, 3, array);}, "");
}


TYPED_TEST(DenseVectorDeathTest_Size8_Stride1, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto vec      = this->vec_;
  const auto offset   = this->offset_;

  EXPECT_DEATH({VectorType vec1(8, 1, vec.getData(), -(offset+1));}, "");
  EXPECT_DEATH({VectorType vec1(8, 1, vec.getData(), 1);}, "");
}


TYPED_TEST(DenseVectorDeathTest_Size8_Stride3, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto vec      = this->vec_;
  const auto offset   = this->offset_;

  EXPECT_DEATH({VectorType vec1(8, 3, vec.getData(), -(offset+1));}, "");
  EXPECT_DEATH({VectorType vec1(8, 3, vec.getData(), 1);}, "");
}
