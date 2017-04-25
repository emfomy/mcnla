#include "../test.hpp"

TYPED_TEST(DenseMatrixTest_ColMajor, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Trans::NORMAL>;

  const auto nrow = 8;
  const auto ncol = 5;

  {
    SCOPED_TRACE("Constructor()");
    MatrixType mat1;

    EXPECT_EQ(mat1.nrow(),  0);
    EXPECT_EQ(mat1.ncol(),  0);
    EXPECT_EQ(mat1.nelem(), 0 * 0);
    EXPECT_EQ(mat1.pitch(), 0);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), 0);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(0, 0)");
    MatrixType mat1(0, 0);

    EXPECT_EQ(mat1.nrow(),  0);
    EXPECT_EQ(mat1.ncol(),  0);
    EXPECT_EQ(mat1.nelem(), 0 * 0);
    EXPECT_EQ(mat1.pitch(), 0);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), 0);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(nrow, ncol)");
    MatrixType mat1(nrow, ncol);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), nrow);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), nrow * ncol);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol})");
    MatrixType mat1(std::make_tuple(nrow, ncol));

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), nrow);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), nrow * ncol);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }
}


TYPED_TEST(DenseMatrixTest_RowMajor, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Trans::TRANS>;

  const auto nrow = 8;
  const auto ncol = 5;

  {
    SCOPED_TRACE("Constructor()");
    MatrixType mat1;

    EXPECT_EQ(mat1.nrow(),  0);
    EXPECT_EQ(mat1.ncol(),  0);
    EXPECT_EQ(mat1.nelem(), 0 * 0);
    EXPECT_EQ(mat1.pitch(), 0);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), 0);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(0, 0)");
    MatrixType mat1(0, 0);

    EXPECT_EQ(mat1.nrow(),  0);
    EXPECT_EQ(mat1.ncol(),  0);
    EXPECT_EQ(mat1.nelem(), 0 * 0);
    EXPECT_EQ(mat1.pitch(), 0);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), 0);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(nrow, ncol)");
    MatrixType mat1(nrow, ncol);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), ncol);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), nrow * ncol);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol})");
    MatrixType mat1(std::make_tuple(nrow, ncol));

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), ncol);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), nrow * ncol);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch8, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Trans::NORMAL>;

  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto memsize  = this->memsize_;
  const auto mat      = this->mat_;

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch)");
    MatrixType mat1(nrow, ncol, pitch);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), pitch * ncol);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), pitch * ncol);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch, memsize)");
    MatrixType mat1(nrow, ncol, pitch, memsize);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), memsize);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch, memsize)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch, memsize);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), memsize);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Copy Constructor");
    MatrixType mat1 = mat;

    EXPECT_EQ(mat1.nrow(),  mat.nrow());
    EXPECT_EQ(mat1.ncol(),  mat.ncol());
    EXPECT_EQ(mat1.nelem(), mat.nelem());
    EXPECT_EQ(mat1.pitch(), mat.pitch());

    EXPECT_EQ(mat1.isShrunk(), mat.isShrunk());

    EXPECT_EQ(mat1.capacity(), mat.capacity());
    EXPECT_EQ(mat1.offset(),   mat.offset());

    EXPECT_EQ(mat1.valPtr(), mat.valPtr());
  }
}


TYPED_TEST(DenseMatrixTest_ColMajor_Size8x5_Pitch10, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Trans::NORMAL>;

  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto memsize  = this->memsize_;
  const auto mat      = this->mat_;

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch)");
    MatrixType mat1(nrow, ncol, pitch);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), pitch * ncol);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), pitch * ncol);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch, memsize)");
    MatrixType mat1(nrow, ncol, pitch, memsize);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), memsize);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch, memsize)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch, memsize);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), memsize);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Copy Constructor");
    MatrixType mat1 = mat;

    EXPECT_EQ(mat1.nrow(),  mat.nrow());
    EXPECT_EQ(mat1.ncol(),  mat.ncol());
    EXPECT_EQ(mat1.nelem(), mat.nelem());
    EXPECT_EQ(mat1.pitch(), mat.pitch());

    EXPECT_EQ(mat1.isShrunk(), mat.isShrunk());

    EXPECT_EQ(mat1.capacity(), mat.capacity());
    EXPECT_EQ(mat1.offset(),   mat.offset());

    EXPECT_EQ(mat1.valPtr(), mat.valPtr());
  }
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch5, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Trans::TRANS>;

  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto memsize  = this->memsize_;
  const auto mat      = this->mat_;

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch)");
    MatrixType mat1(nrow, ncol, pitch);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), nrow * pitch);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), nrow * pitch);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch, memsize)");
    MatrixType mat1(nrow, ncol, pitch, memsize);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), memsize);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch, memsize)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch, memsize);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_TRUE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), memsize);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Copy Constructor");
    MatrixType mat1 = mat;

    EXPECT_EQ(mat1.nrow(),  mat.nrow());
    EXPECT_EQ(mat1.ncol(),  mat.ncol());
    EXPECT_EQ(mat1.nelem(), mat.nelem());
    EXPECT_EQ(mat1.pitch(), mat.pitch());

    EXPECT_EQ(mat1.isShrunk(), mat.isShrunk());

    EXPECT_EQ(mat1.capacity(), mat.capacity());
    EXPECT_EQ(mat1.offset(),   mat.offset());

    EXPECT_EQ(mat1.valPtr(), mat.valPtr());
  }
}


TYPED_TEST(DenseMatrixTest_RowMajor_Size8x5_Pitch10, Constructor) {
  using MatrixType = mcnla::matrix::DenseMatrix<TypeParam, mcnla::Trans::TRANS>;

  const auto nrow     = this->nrow_;
  const auto ncol     = this->ncol_;
  const auto pitch    = this->pitch_;
  const auto memsize  = this->memsize_;
  const auto mat      = this->mat_;

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch)");
    MatrixType mat1(nrow, ncol, pitch);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), nrow * pitch);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), nrow * pitch);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor(nrow, ncol, pitch, memsize)");
    MatrixType mat1(nrow, ncol, pitch, memsize);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), memsize);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Constructor({nrow, ncol}, pitch, memsize)");
    MatrixType mat1(std::make_tuple(nrow, ncol), pitch, memsize);

    EXPECT_EQ(mat1.nrow(),  nrow);
    EXPECT_EQ(mat1.ncol(),  ncol);
    EXPECT_EQ(mat1.nelem(), nrow * ncol);
    EXPECT_EQ(mat1.pitch(), pitch);

    EXPECT_FALSE(mat1.isShrunk());

    EXPECT_EQ(mat1.capacity(), memsize);
    EXPECT_EQ(mat1.offset(),   0);

    mat1.vectorize();
  }

  {
    SCOPED_TRACE("Copy Constructor");
    MatrixType mat1 = mat;

    EXPECT_EQ(mat1.nrow(),  mat.nrow());
    EXPECT_EQ(mat1.ncol(),  mat.ncol());
    EXPECT_EQ(mat1.nelem(), mat.nelem());
    EXPECT_EQ(mat1.pitch(), mat.pitch());

    EXPECT_EQ(mat1.isShrunk(), mat.isShrunk());

    EXPECT_EQ(mat1.capacity(), mat.capacity());
    EXPECT_EQ(mat1.offset(),   mat.offset());

    EXPECT_EQ(mat1.valPtr(), mat.valPtr());
  }
}
