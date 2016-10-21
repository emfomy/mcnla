#include "../death_test.hpp"

TYPED_TEST(DenseVectorDeathTest, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;
  using ArrayType  = mcnla::matrix::Array<TypeParam>;

  ArrayType array(25, 4);

  EXPECT_DEATH(VectorType vec1(-1), "");
  EXPECT_DEATH(VectorType vec1(0, 0), "");
  EXPECT_DEATH(VectorType vec1(8, 3, 21), "");
  EXPECT_DEATH(VectorType vec1(8, 3, array), "");
}


TYPED_TEST(DenseVectorDeathTest_Size8_Stride1, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto offset   = this->offset_;
  const auto vec      = this->vec_;
  const auto length   = this->length_;
  const auto stride   = this->stride_;

  EXPECT_DEATH(VectorType vec1(length, stride, vec.getData(), -(offset+1)), "");
  EXPECT_DEATH(VectorType vec1(length, stride, vec.getData(), 1), "");
}


TYPED_TEST(DenseVectorDeathTest_Size8_Stride3, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  const auto offset   = this->offset_;
  const auto vec      = this->vec_;
  const auto length   = this->length_;
  const auto stride   = this->stride_;

  EXPECT_DEATH(VectorType vec1(length, stride, vec.getData(), -(offset+1)), "");
  EXPECT_DEATH(VectorType vec1(length, stride, vec.getData(), 1), "");
}
