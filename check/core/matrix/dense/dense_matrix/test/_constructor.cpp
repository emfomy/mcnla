#include "../test.hpp"

TYPED_TEST(DenseMatrixTest_ColMajor, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Layout::COLMAJOR>;

  const auto nrow = 8;
  const auto ncol = 5;

  {
    MatrixType mat1;

    EXPECT_EQ(mat1.getNrow(),  0);
    EXPECT_EQ(mat1.getNcol(),  0);
    EXPECT_EQ(mat1.getNelem(), 0 * 0);
    EXPECT_EQ(mat1.getSizes(), std::make_pair(0, 0));
    EXPECT_EQ(mat1.getPitch(), 1);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), 0);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    MatrixType mat1(nrow, ncol);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getSizes(), std::make_pair(nrow, ncol));
    EXPECT_EQ(mat1.getPitch(), nrow);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), nrow * ncol);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }
}

#pragma warning imcomplete