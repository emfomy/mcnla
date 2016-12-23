#include "../test.hpp"

TYPED_TEST(DenseMatrixTest_ColMajor, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Layout::COLMAJOR>;

  const auto nrow = 8;
  const auto ncol = 5;

  {
    SCOPED_TRACE("Constructor()");
    MatrixType mat1;

    EXPECT_EQ(mat1.getNrow(),  0);
    EXPECT_EQ(mat1.getNcol(),  0);
    EXPECT_EQ(mat1.getNelem(), 0 * 0);
    EXPECT_EQ(mat1.getPitch(), 0);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), 0);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(0, 0)");
    MatrixType mat1(0, 0);

    EXPECT_EQ(mat1.getNrow(),  0);
    EXPECT_EQ(mat1.getNcol(),  0);
    EXPECT_EQ(mat1.getNelem(), 0 * 0);
    EXPECT_EQ(mat1.getPitch(), 0);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), 0);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(nrow, ncol)");
    MatrixType mat1(nrow, ncol);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), nrow);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), nrow * ncol);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol})");
    MatrixType mat1(std::make_tuple(nrow, ncol));

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), nrow);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), nrow * ncol);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }
}


TYPED_TEST(DenseMatrixTest_RowMajor, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Layout::ROWMAJOR>;

  const auto nrow = 8;
  const auto ncol = 5;

  {
    SCOPED_TRACE("Constructor()");
    MatrixType mat1;

    EXPECT_EQ(mat1.getNrow(),  0);
    EXPECT_EQ(mat1.getNcol(),  0);
    EXPECT_EQ(mat1.getNelem(), 0 * 0);
    EXPECT_EQ(mat1.getPitch(), 0);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), 0);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(0, 0)");
    MatrixType mat1(0, 0);

    EXPECT_EQ(mat1.getNrow(),  0);
    EXPECT_EQ(mat1.getNcol(),  0);
    EXPECT_EQ(mat1.getNelem(), 0 * 0);
    EXPECT_EQ(mat1.getPitch(), 0);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), 0);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(nrow, ncol)");
    MatrixType mat1(nrow, ncol);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), ncol);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), nrow * ncol);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol})");
    MatrixType mat1(std::make_tuple(nrow, ncol));

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), ncol);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), nrow * ncol);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Layout::COLMAJOR>;

  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto memsize  = this->memsize_;
  const auto mat      = this->mat_;

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch)");
    MatrixType mat1(nrow, ncol, pitch);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), pitch * ncol);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), pitch * ncol);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch, memsize)");
    MatrixType mat1(nrow, ncol, pitch, memsize);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), memsize);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch, memsize)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch, memsize);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), memsize);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Copy Constructor");
    MatrixType mat1 = mat;

    EXPECT_EQ(mat1.getNrow(),  mat.getNrow());
    EXPECT_EQ(mat1.getNcol(),  mat.getNcol());
    EXPECT_EQ(mat1.getNelem(), mat.getNelem());
    EXPECT_EQ(mat1.getPitch(), mat.getPitch());

    EXPECT_EQ(mat1.isShrunk(), mat.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), mat.getCapacity());
    EXPECT_EQ(mat1.getOffset(),   mat.getOffset());

    EXPECT_EQ(mat1.getValuePtr(), mat.getValuePtr());


    SCOPED_TRACE("Move Constructor");
    MatrixType mat2 = std::move(mat1);

    EXPECT_EQ(mat1.getNrow(),  0);
    EXPECT_EQ(mat1.getNcol(),  0);
    EXPECT_EQ(mat1.getNelem(), 0);
    EXPECT_EQ(mat1.getPitch(), 0);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), 0);
    EXPECT_EQ(mat1.getOffset(),   0);


    EXPECT_EQ(mat2.getNrow(),  mat.getNrow());
    EXPECT_EQ(mat2.getNcol(),  mat.getNcol());
    EXPECT_EQ(mat2.getNelem(), mat.getNelem());
    EXPECT_EQ(mat2.getPitch(), mat.getPitch());

    EXPECT_EQ(mat2.isShrunk(), mat.isShrunk());

    EXPECT_EQ(mat2.getCapacity(), mat.getCapacity());
    EXPECT_EQ(mat2.getOffset(),   mat.getOffset());

    EXPECT_EQ(mat2.getValuePtr(), mat.getValuePtr());
  }
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Layout::COLMAJOR>;

  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto memsize  = this->memsize_;
  const auto mat      = this->mat_;

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch)");
    MatrixType mat1(nrow, ncol, pitch);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), pitch * ncol);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), pitch * ncol);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch, memsize)");
    MatrixType mat1(nrow, ncol, pitch, memsize);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), memsize);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch, memsize)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch, memsize);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), memsize);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Copy Constructor");
    MatrixType mat1 = mat;

    EXPECT_EQ(mat1.getNrow(),  mat.getNrow());
    EXPECT_EQ(mat1.getNcol(),  mat.getNcol());
    EXPECT_EQ(mat1.getNelem(), mat.getNelem());
    EXPECT_EQ(mat1.getPitch(), mat.getPitch());

    EXPECT_EQ(mat1.isShrunk(), mat.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), mat.getCapacity());
    EXPECT_EQ(mat1.getOffset(),   mat.getOffset());

    EXPECT_EQ(mat1.getValuePtr(), mat.getValuePtr());


    SCOPED_TRACE("Move Constructor");
    MatrixType mat2 = std::move(mat1);

    EXPECT_EQ(mat1.getNrow(),  0);
    EXPECT_EQ(mat1.getNcol(),  0);
    EXPECT_EQ(mat1.getNelem(), 0);
    EXPECT_EQ(mat1.getPitch(), 0);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), 0);
    EXPECT_EQ(mat1.getOffset(),   0);


    EXPECT_EQ(mat2.getNrow(),  mat.getNrow());
    EXPECT_EQ(mat2.getNcol(),  mat.getNcol());
    EXPECT_EQ(mat2.getNelem(), mat.getNelem());
    EXPECT_EQ(mat2.getPitch(), mat.getPitch());

    EXPECT_EQ(mat2.isShrunk(), mat.isShrunk());

    EXPECT_EQ(mat2.getCapacity(), mat.getCapacity());
    EXPECT_EQ(mat2.getOffset(),   mat.getOffset());

    EXPECT_EQ(mat2.getValuePtr(), mat.getValuePtr());
  }
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Layout::ROWMAJOR>;

  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto memsize  = this->memsize_;
  const auto mat      = this->mat_;

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch)");
    MatrixType mat1(nrow, ncol, pitch);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), nrow * pitch);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), nrow * pitch);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch, memsize)");
    MatrixType mat1(nrow, ncol, pitch, memsize);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), memsize);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch, memsize)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch, memsize);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), memsize);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Copy Constructor");
    MatrixType mat1 = mat;

    EXPECT_EQ(mat1.getNrow(),  mat.getNrow());
    EXPECT_EQ(mat1.getNcol(),  mat.getNcol());
    EXPECT_EQ(mat1.getNelem(), mat.getNelem());
    EXPECT_EQ(mat1.getPitch(), mat.getPitch());

    EXPECT_EQ(mat1.isShrunk(), mat.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), mat.getCapacity());
    EXPECT_EQ(mat1.getOffset(),   mat.getOffset());

    EXPECT_EQ(mat1.getValuePtr(), mat.getValuePtr());


    SCOPED_TRACE("Move Constructor");
    MatrixType mat2 = std::move(mat1);

    EXPECT_EQ(mat1.getNrow(),  0);
    EXPECT_EQ(mat1.getNcol(),  0);
    EXPECT_EQ(mat1.getNelem(), 0);
    EXPECT_EQ(mat1.getPitch(), 0);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), 0);
    EXPECT_EQ(mat1.getOffset(),   0);


    EXPECT_EQ(mat2.getNrow(),  mat.getNrow());
    EXPECT_EQ(mat2.getNcol(),  mat.getNcol());
    EXPECT_EQ(mat2.getNelem(), mat.getNelem());
    EXPECT_EQ(mat2.getPitch(), mat.getPitch());

    EXPECT_EQ(mat2.isShrunk(), mat.isShrunk());

    EXPECT_EQ(mat2.getCapacity(), mat.getCapacity());
    EXPECT_EQ(mat2.getOffset(),   mat.getOffset());

    EXPECT_EQ(mat2.getValuePtr(), mat.getValuePtr());
  }
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Layout::ROWMAJOR>;

  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto memsize  = this->memsize_;
  const auto mat      = this->mat_;

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch)");
    MatrixType mat1(nrow, ncol, pitch);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), nrow * pitch);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), nrow * pitch);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch, memsize)");
    MatrixType mat1(nrow, ncol, pitch, memsize);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), memsize);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch, memsize)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch, memsize);

    EXPECT_EQ(mat1.getNrow(),  nrow);
    EXPECT_EQ(mat1.getNcol(),  ncol);
    EXPECT_EQ(mat1.getNelem(), nrow * ncol);
    EXPECT_EQ(mat1.getPitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), memsize);
    EXPECT_EQ(mat1.getOffset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Copy Constructor");
    MatrixType mat1 = mat;

    EXPECT_EQ(mat1.getNrow(),  mat.getNrow());
    EXPECT_EQ(mat1.getNcol(),  mat.getNcol());
    EXPECT_EQ(mat1.getNelem(), mat.getNelem());
    EXPECT_EQ(mat1.getPitch(), mat.getPitch());

    EXPECT_EQ(mat1.isShrunk(), mat.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), mat.getCapacity());
    EXPECT_EQ(mat1.getOffset(),   mat.getOffset());

    EXPECT_EQ(mat1.getValuePtr(), mat.getValuePtr());


    SCOPED_TRACE("Move Constructor");
    MatrixType mat2 = std::move(mat1);

    EXPECT_EQ(mat1.getNrow(),  0);
    EXPECT_EQ(mat1.getNcol(),  0);
    EXPECT_EQ(mat1.getNelem(), 0);
    EXPECT_EQ(mat1.getPitch(), 0);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.getCapacity(), 0);
    EXPECT_EQ(mat1.getOffset(),   0);


    EXPECT_EQ(mat2.getNrow(),  mat.getNrow());
    EXPECT_EQ(mat2.getNcol(),  mat.getNcol());
    EXPECT_EQ(mat2.getNelem(), mat.getNelem());
    EXPECT_EQ(mat2.getPitch(), mat.getPitch());

    EXPECT_EQ(mat2.isShrunk(), mat.isShrunk());

    EXPECT_EQ(mat2.getCapacity(), mat.getCapacity());
    EXPECT_EQ(mat2.getOffset(),   mat.getOffset());

    EXPECT_EQ(mat2.getValuePtr(), mat.getValuePtr());
  }
}
