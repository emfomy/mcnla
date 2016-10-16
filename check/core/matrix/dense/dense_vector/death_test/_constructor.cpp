#include "../death_test.hpp"

TYPED_TEST(DenseVectorDeathTest, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;
  using ArrayType  = mcnla::matrix::Array<TypeParam>;

  ArrayType array(25, 4);

  EXPECT_DEATH(VectorType vec(8, 0), "");
  EXPECT_DEATH(VectorType vec(8, 3, 21), "");
  EXPECT_DEATH(VectorType vec(8, 3, array), "");
}


TYPED_TEST(DenseVectorDeathTest_Size8_Stride1, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto offset   = this->offset_;
  const auto vec      = this->vec_;

  EXPECT_DEATH(VectorType vec1(8, 1, vec.getData(), -(offset+1)), "");
  EXPECT_DEATH(VectorType vec1(8, 1, vec.getData(), 1), "");
}


TYPED_TEST(DenseVectorDeathTest_Size8_Stride3, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto offset   = this->offset_;
  const auto vec      = this->vec_;

  EXPECT_DEATH(VectorType vec1(8, 3, vec.getData(), -(offset+1)), "");
  EXPECT_DEATH(VectorType vec1(8, 3, vec.getData(), 1), "");
}
