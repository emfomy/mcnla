#include "../death_test.hpp"

TYPED_TEST(DenseVectorDeathTest, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;

  EXPECT_DEATH(VectorType vec1(-1), "");
  EXPECT_DEATH(VectorType vec1(0, 0), "");
  EXPECT_DEATH(VectorType vec1(1, 0), "");
}


TYPED_TEST(DenseVectorDeathTest_Size8_Stride1, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;
  using ArrayType  = mcnla::matrix::Array<TypeParam>;

  const auto len      = this->len_;
  const auto stride   = this->stride_;
  const auto memsize  = this->memsize_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto vec      = this->vec_;

  ArrayType array(memsize, offset+1);

  EXPECT_DEATH(VectorType vec1(len, stride, array), "");
  EXPECT_DEATH(VectorType vec1(len, stride, capacity-1), "");
  EXPECT_DEATH(VectorType vec1(len, stride, vec.val(), -(offset+1)), "");
  EXPECT_DEATH(VectorType vec1(len, stride, vec.val(), 1), "");
}


TYPED_TEST(DenseVectorDeathTest_Size8_Stride3, Constructor) {
  using VectorType = mcnla::matrix::DenseVector<TypeParam>;
  using ArrayType  = mcnla::matrix::Array<TypeParam>;

  const auto len      = this->len_;
  const auto stride   = this->stride_;
  const auto memsize  = this->memsize_;
  const auto capacity = this->capacity_;
  const auto offset   = this->offset_;
  const auto vec      = this->vec_;

  ArrayType array(memsize, offset+1);

  EXPECT_DEATH(VectorType vec1(len, stride, array), "");
  EXPECT_DEATH(VectorType vec1(len, stride, capacity-1), "");
  EXPECT_DEATH(VectorType vec1(len, stride, vec.val(), -(offset+1)), "");
  EXPECT_DEATH(VectorType vec1(len, stride, vec.val(), 1), "");
}
