#include "../death_test.hpp"

TYPED_TEST(DenseMatrixDeathTest_ColMajor, Constructor) {
  using MatrixType = mcnla::container::DenseMatrix<TypeParam, mcnla::Trans::NORMAL>;

  const auto nrow = 8;
  const auto ncol = 5;

  EXPECT_DEATH(MatrixType mat(-1, 0), "");
  EXPECT_DEATH(MatrixType mat(0, -1), "");
  EXPECT_DEATH(MatrixType mat(-1, -1), "");
  EXPECT_DEATH(MatrixType mat(0, 0, -1), "");
  EXPECT_DEATH(MatrixType mat(nrow, ncol, nrow-1), "");
}


TYPED_TEST(DenseMatrixDeathTest_RowMajor, Constructor) {
  using MatrixType = mcnla::container::DenseMatrix<TypeParam, mcnla::Trans::TRANS>;

  const auto nrow = 8;
  const auto ncol = 5;

  EXPECT_DEATH(MatrixType mat(-1, 0), "");
  EXPECT_DEATH(MatrixType mat(0, -1), "");
  EXPECT_DEATH(MatrixType mat(-1, -1), "");
  EXPECT_DEATH(MatrixType mat(0, 0, -1), "");
  EXPECT_DEATH(MatrixType mat(nrow, ncol, ncol-1), "");
}
