#include "../death_test.hpp"

TYPED_TEST(DenseMatrixDeathTest_ColMajor, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Layout::COLMAJOR>;
  // using ArrayType  = mcnla::matrix::Array<TypeParam>;

  // ArrayType array(25, 4);

  EXPECT_DEATH(MatrixType mat(-1, 1), "");
  EXPECT_DEATH(MatrixType mat(1, -1), "");
  EXPECT_DEATH(MatrixType mat(-1, -1), "");
}


TYPED_TEST(DenseMatrixDeathTest_RowMajor, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Layout::ROWMAJOR>;
  // using ArrayType  = mcnla::matrix::Array<TypeParam>;

  // ArrayType array(25, 4);

  EXPECT_DEATH(MatrixType mat(-1, 1), "");
  EXPECT_DEATH(MatrixType mat(1, -1), "");
  EXPECT_DEATH(MatrixType mat(-1, -1), "");
}
